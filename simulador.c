#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cumunes.h"
#include "simulador.h"

/*TO DO: 	escribir bien handle_error con todos los estado (hacerlo al final por las dudas de agregar más estados)
			*/


int main(int argc, char const *argv[])
{
	status_t st;
	char* model_filename, output_filename;
	formato_t fmt;
	FILE* model_fp, output_fp;


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

	if ( (output_fp = fopen_fmt(output_filename,fmt)) == NULL ) 
	{
		handle_error(ST_UNABLE_TO_OPEN_FILE);
		return EXIT_FAILURE;
	}



	/***********************
	PARTE DEL CODIGO PARA PROCESAR EL ARCHIVO




	**********************/

	/***********************
	PARTE DEL CODIGO PARA HACER LA SIMULACIÓN
	mirar las funciones que arme generarmensaje y procesarmensaje


	
	**********************/


	return 0;
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
				return fopen(filename,"wt")
				break;
			default:
				return NULL;
		}
	}



char** split (const char *s, char delim, size_t *cant_fields,status_t* st){

	char **csvfields,**aux;
	int i,j=0,n=1;
	char* dup;

	if (cant_fields==NULL){
		*st=ST_NULL_POINTER;
		return NULL;
	}

	if (s==NULL){
		*st=ST_NULL_POINTER;
		*fields=0;
		return NULL;
	}

	if((dup=strdup(s))==NULL){
		*st=ST_NO_MEM;
		*cant_fields=0;
		return NULL;
	}

	if((aux=(char**)calloc(n,sizeof(char*)))==NULL){
		*st=ST_NO_MEM;
		*fields=0;
		return NULL;
	}
	csvfields=aux;
	csvfields[j]=dup;

	for (i=0,j=1;dup[i];i++){
		if (dup[i]==delim){
			dup[i]='\0';
			if((dup[i+1]!=delim && dup[i+1]!='\0')){

				if((aux=(char**)realloc(csvfields,(++n)*sizeof(char*)))==NULL){
					free(csvfields);
					*st=ST_NO_MEM;
					*fields=0;
					return NULL;
				}
				csvfields=aux;
				csvfields[j]=&dup[i+1];
				j++;
			}

		}
	}
	*cant_fields=n;
	*st=ST_OK;
	return csvfields;
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
	/*Ver si se pueden usar macros*/
	char* LEXEM = "HOUSE";
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

