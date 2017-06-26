/*    https://github.com/franconastasi/Algo1_TP_Final    */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "cumunes.h"
#include "simulador.h"

/*TO DO: 	escribir bien handle_error con todos los estado (hacerlo al final por las dudas de agregar más estados)
			*/
status_t split (const char *, char, size_t *,char***);


int main(int argc, char const *argv[])
{
	status_t st;
	char* model_filename, output_filename;
	formato_t fmt;
	FILE* model_fp, output_fp;
	sensor_t** arr_sensores;
	size_t *n_sensores;
	size_t n_iteraciones;
	size_t cant_msg_generar;
	size_t cant_msg_procesar;
	size_t i, j;
	lista lista_msg;

	if ((st = validar_arg(argc,argv,model_filename,&fmt,output_filename)) != ST_OK)
	{
		handle_error(st);
		return EXIT_FAILURE;
	}

	if ( (model_fp = fopen(model_filename,"rt")) == NULL )
	{
		handle_error(ST_UNABLE_TO_OPEN_FILE);
		return EXIT_FAILURE;
	}

	if
	if ( (output_fp = fopen_fmt(output_filename,fmt)) == NULL )
	{
		handle_error(ST_UNABLE_TO_OPEN_FILE);
		return EXIT_FAILURE;
	}

	if ((st = lista_crear(&lista_msg) ) != ST_OK){
		handle_error(st);
		return EXIT_FAILURE;
	}

	/***********************
	PARTE DEL CODIGO PARA PROCESAR EL ARCHIVO
	**********************/
	if( st = crear_arreglo_sensores_modelo(&arr_sensores,n_sensores,model_fp) != ST_OK ){
		handle_error(st);
		return EXIT_FAILURE;
	}


	/***********************
	PARTE DEL CODIGO PARA HACER LA SIMULACIÓN
	mirar las funciones que arme generarmensaje y procesarmensaje
	**********************/


	srand(time(NULL));
	for (n_iteraciones = 0; i < CANT_ITERACIONES; ++i)
	{
		/* cant_msg_generar es de tipo size_t por lo tanto puede representar a un numero entre 0 y sizeof(size_t) * 8 */
		cant_msg_generar = rand() % (sizeof(size_t) * 8)
		if ( (st = generarMensajes(cant_msg_generar, &lista_msg, arr_sensores, n_sensores)) != ST_OK){
			handle_error(st);
			return EXIT_FAILURE;
		}
		cant_msg_procesar = rand() % (sizeof(size_t) * 8);
		if ( (st = procesarMensajes(cant_msg_procesar, &lista_msg,fmt, output_fp)) != ST_OK){
			switch(st){
				case ST_OK:
					break;
				case ST_LISTA_VACIA:
					continue;
					break;
				default:
					handle_error(st);
					return EXIT_FAILURE;
			}
		}
	}
	lista_destruir(&lista_msg, /*poner una función que destruya el nodo*/)
	destruir_arreglo_sensor(&arr_sensores,n_sensores)
	fclose(model_fp);
	fclose(output_fp);

	return EXIT_SUCCESS;
}





status_t validar_arg(int argc, const char* argv[], char* model_filename, *formato_t fmt ,char* output_filename){
	int model_pos, ftm_pos, output_pos;

	if (argc != CANT_ARG){
			return ST_INVALID_CANT_ARG;
		}
		/*obtengo posiciones*/
	model_pos = obtener_pos(PARAM_MODEL,argc, argv);
	ftm_pos = obtener_pos(PARAM_FORMAT,argc, argv);
	output_pos = obtener_pos(PARAM_FILE_MSG,argc, argv);
	/*chequeo que todas esten dentro de argv*/
	if (model_pos == argc || ftm_pos == argc || output_pos == argc ){
		return ST_ARG_NOT_FOUND;
	}
	/* Las copio a cada variable*/
	strcpy(model_filename,argv[model_pos]);

	if (*fmt = str_to_ftm(argv[ftm_pos]) == CANT_FMT){
		return ST_INVALID_ARG_FMT;
	}

	strcpy(output_filename,argv[output_pos]);

	return ST_OK;
}


int obtener_pos(char* elem,int n_max_elem, char* str_array[]){
	int i;

	for (i = 0; i < n_max_elem; ++i)
	{
		if (strcmp(elem, str_array[i]))
		{
			return (i+1)
		}
	}
	return i;
}

formato_t str_to_ftm(char * str){
	int i;
	char* ftm_strings[] = {
		BIN_FMT_STR,
		CSV_FMT_STR
	};

	for (i = 0; i < CANT_FMT; ++i)
	{
		if(!strcmp(str,ftm_strings[i])){
			return i;
		}
	}
	return i;
}

FILE* fopen_fmt(char* filename, formato_t fmt){
		if (!filename){
			return NULL;
		}
		switch(fmt){
			case BIN:
				return fopen(filename,"wb")
				/*tecnicamente el break no sería necesario;*/
				break;
			case CSV:
				if(filename == STD_OUT_PARAM){
					/* 	Esto puede parecer raro pero hice una prueba y si a una variable FILE* le asignas stdout (fp = stdout) y
						llamas a fprintf (fprintf(fp;"%s\n"; "wubba lubba dub dub"))  lo imprime bien */
					return stdout;
				}else{
					return fopen(filename,"wt")
					break;
				}
			default:
				return NULL;
		}
	}



status_t split (const char *s, char delim, size_t *cant_fields,char*** csvfields){

	char **aux;
	int i,j=0,n=1;
	char* dup;


	if (!cant_fields || !csvfields ){
		return ST_NULL_POINTER;
	}

	if (s==NULL){
		*cant_fields=0;
		return ST_NULL_POINTER;
	}

	if((dup=strdup(s))==NULL){
		*cant_fields=0;
		return ST_NO_MEM;
	}

	if((aux=(char**)calloc(n,sizeof(char*)))==NULL){
		*cant_fields=0;
		return ST_NO_MEM;
	}
	(*csvfields)=aux;
	(*csvfields)[j]=dup;

	for (i=0,j=1;dup[i];i++){
		if (dup[i]==delim){
			dup[i]='\0';
			if((dup[i+1]!=delim && dup[i+1]!='\0')){

				if((aux=(char**)realloc((*csvfields),(++n)*sizeof(char*)))==NULL){
					free((*csvfields));
					*cant_fields=0;
					return ST_NO_MEM;
				}
				(*csvfields)=aux;
				(*csvfields)[j]=&dup[i+1];
				j++;
			}
		}
	}
	*cant_fields=n;
	return ST_OK;
}

char* strdup (const char *str){
	char* str2;
	if((str2=(char*)calloc(((strlen(str))+1),sizeof(char)))==NULL){
		return NULL;
	}
	strcpy(str2,str);
	return str2;
}


/* Agrega mensajes a la lista */
/* el paramentro n viene del main */
status_t generarMensajes(size_t n, lista_t* l,sensor_t ** sens, size_t n_sens){
	size_t i,j;
	for (i = 0; i < n; ++i){
		j = rand() % n_sens;
		return lista_insertar_final(l,SENSOR_adquirir_datos(sens[j]));
	}
}

/* el paramentro m viene del main */
status_t procesarMensajes(size_t m, lista_t* l,formato_t fmt, FILE* fp){
	size_t i;
	status_t st;
	nodo_t* nodo;
	if(lista_esta_vacia(l)){
		return ST_LISTA_VACIA;
	}
	status_t (*fn[CANT_FUNC_PROC])(lista*l,FILE* fp)={
		procesarMensajeBIN,
		procesarMensajeCSV
	};

	for(i = 0; i< m; i++){
		if( ( st = (*fn[fmt])(l,fp)) != ST_OK){
			return st;
		}
		nodo = *l;
		l = &(*l->sig);
		lista_destruir_nodo(&nodo, /*poner una función que destruya el nodo*/)
	}
}


status_t procesarMensajeBIN(lista_t* l, FILE* fp){
	/* TO DO: Ver como hacer esto con macros */
	char LEXEM[] = {'H','O','U','S','E'};
	char FIN = SUFIX_END;

	if (!l || !fp)
	{
		return ST_NULL_POINTER;
	}

	if ( fwrite(LEXEM,sizeof(LEXEM),1,fp) != 1  )
	{
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}
	if ( fwrite(&((*l)->largo), sizeof((*l)->largo) + sizeof((*l)->id) +  sizeof((*l)->sub_id) ,1,fp) != 1  )
	{
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}

	if ( fwrite((*l)->datos, (*l)->largo * sizeof(*((*l)->datos)),1,fp) != 1  )
	{
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}

	if ( fwrite(&FIN, sizeof(FIN),1,fp) != 1  )
	{
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}

	return ST_OK;


}
status_t procesarMensajeCSV(lista_t* l, FILE* fp){
	char* LEXEM = PREFIX_LEXEM_CSV;
	char FIN, delim;
	int i;

	FIN = SUFIX_END;
	delim = CSV_DELIM;

	if (!l || !fp)
	{
		return ST_NULL_POINTER;
	}

	fprintf(fp, "%s%c%lu%c%i%c%i%c", LEXEM, delim, (*l)->largo, delim, (*l)->id, delim,(*l)->sub_id, delim);

	for (i = 0; i < (*l)->largo; ++i)
	{
		fprintf(fp, "%u%c", ((*l)->datos)[i], delim );
	}

	fprintf(fp, "%c\n", FIN);

	return ST_OK;
}















/* Revisar esta función: st no está declarado?
*/


status_t read_line_modelo (FILE* srcf,char** line, bool_t* eof){

	char *aux;
	int c;
	size_t alloc_size=INITSIZE, used_size=0;

	if(line==NULL)
		return ST_NULL_POINTER;
	if (!srcf || !eof){
		(*line)=NULL;
		return ST_NULL_POINTER;
	}
	if((*line)=(char*)calloc(INITSIZE,sizeof(char))==NULL){
		*line=NULL;
		return ST_NO_MEM;
	}
	if((c=fgetc(srcf))=='\n' || c==COMMENT_CHAR){
		(*line)=NULL;
		return ST_OK;
	}
	if(c==EOF){
		*eof=TRUE;
		(*line)=NULL;
		return  ST_OK;
	}

	(*line)[used_size]=c;
	used_size++;

	while(((c=fgetc(srcf)) != '\n') && (c != EOF)) {
		if(used_size==alloc_size){
			if((aux=(char*)realloc(*line,sizeof(char)*(alloc_size+CHOP_SIZE)))==NULL){
				return ST_NO_MEM;
				free(*line);
				(*line)=NULL;
			}
			(*line)=aux;
		}

		(*line)[used_size]=c;
		used_size++;
		alloc_size+=CHOP_SIZE;
	}

	if((aux=(char*)realloc(*line,sizeof(char)*(++used_size)) )==NULL){
		return ST_NO_MEM;
		free(*line);
		(*line)=NULL;
	}

	(*line)=aux;
	(*line)[used_size]='\0';

	return ST_OK;
}

status crear_arreglo_sensores_modelo(sensor_t***arr_sensores,size_t* cant_sensores, FILE* ptrf_model){

  sensor_type_t id;
  int sub_id;
  char * model_line,*endptr;
  bool_t *eof;
  size_t n=1;
  size_t cant,numparam;
  char ** campos_model
  double * parametros;
  sensor_t * sensor,**aux;

  if(!arr_sensores || !cant_sensores){
      return ST_NULL_POINTER;
  }

  (*arr_sensores)=NULL;

  do{
      if((st=read_line(ptrf_model,&model_line,&eof)!=ST_SUCCESS)
        return ST_ERROR_LEER_MODELO;
      if((*model_line)==NULL)
        continue;
      if((st=split(model_line,DELIM,&cant,&campos_model))!=ST_SUCCESS)
        return st;
      if((st=obtener_id(campos_model[ID_POS]),&id)!=ST_OK)
        return st;
      if((st=obtener_subid(campos_model[ID_POS]),&sub_id)!=ST_OK)
        return st;
      numparam=cant-2;
      if((st=obtener_params(campos_model,&parametros,numparam))!=ST_OK)
        return st;

      if(aux=(sensor_t**)realloc((*arr_sensores),(*cant_sensores)*sizeof(sensor_t*)))==NULL){
        destruir_arreglo_sensor(arr_sensores,cant_sensores);
        return ST_NO_MEM;
      }
      *arr_sensores=aux;

      switch(id){

        case SENSOR_IMU:
          if ((st=IMU_crear(&sensor,id,sub_id,parametros,numparam))!=ST_OK){
            destruir_arreglo_sensor(arr_sensores,cant_sensores);
          }
          break;

        case SENSOR_GPS:
          if ((st=GPS_crear(&sensor,id,sub_id,parametros,numparam))!=ST_OK){
            destruir_arreglo_sensor(arr_sensores,cant_sensores);
            return st;
          }
          break;

        case SENSOR_US:
          if ((st=IMU_crear(&sensor,id,sub_id,parametros,numparam))!=ST_OK){
            destruir_arreglo_sensor(arr_sensores,cant_sensores);
            return st;
          }
          break;

      }
      (*arr_sensores)[cant_sensores-1]=sensor;
      *cant_sensores++;

    } while (*eof==FALSE);

  return ST_OK;

}

status_t obtener_id(char* id_string,sensor_type_t *id){
  if (!id || !id_string ){
    return ST_NULL_POINTER;
  }
  if (strcmp(id_string,IMU_ID)==0){/*IMU_ID  Y TODOS LOS XX_ID SON MACROS A DEFINIR*/
    *id=SENSOR_IMU;
    return ST_OK;
  }
  if (strcmp(id_string,GPS_ID)==0){
    *id=SENSOR_GPS;
    return ST_OK;
  }
  if (strcmp(id_string,US_ID)==0){
   *id=SENSOR_US;
   return ST_OK;
  }
  return ST_INVALID_ID;
}

status_t obtener_subid (char*subid_string,int* sub_id){
  if (!sub_id || !id_string )
    return ST_NULL_POINTER;

  *sub_id=(int)strtod(campos_model[SUB_ID_POS],&endptr);
  if(*endptr != '\0')
    return ST_INVALID_SUBID;
}

status_t obtener_params (char**params_array,double** params,size_t cant){
  size_t i;
  char * endptr;

  if(!params_array || !params)
    return ST_NULL_POINTER;
  if((*params=(double*)calloc(cant,sizeof(double)))==NULL)
    return ST_NO_MEM;

  for(i=0;i<cant;i++){
    (*params)[i]=strtod(params_array[i+2],&endptr)
    if(*endptr != '\0'){
      free(*params);
      *params=NULL;
      return ST_INVALID_PARAMS;
    }
  }
  return ST_OK;
}
void destruir_arreglo_sensor(sensor_t*** arr_sensores,size_t *cant_sensores){
  size_t i;

  if(!arr_sensores || !cant_sensores)
    return;

  for(i=0;i<*cant_sensores;i++){
    switch(((*arr_sensores)[i])->id){
      case SENSOR_IMU:
        IMU_destruir(&((*arr_sensores)[i]));

      case SENSOR_GPS:
        GPS_destruir(&((*arr_sensores)[i]));

      case SENSOR_US:
        US_destruir(&((*arr_sensores)[i]));
    }
  }
  free(*arr_sensores);
  *arr_sensores=NULL;
  *cant_sensores=0;
}
