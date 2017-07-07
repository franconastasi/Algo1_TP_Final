/*    https://github.com/franconastasi/Algo1_TP_Final    */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "sensor.h"
#include "comunes.h"
#include "simulador.h"
#include "GPS.h"
#include "IMU.h"
#include "ultrasonido.h"
#include "lista.h"


int main(int argc, char const *argv[])
{
	status_t st;
	char *model_filename, *output_filename;
	formato_t fmt;
	FILE *model_fp, *output_fp;
	sensor_t **arr_sensores;
	size_t n_sensores, n_iteraciones, cant_msg_generar, cant_msg_procesar;
	lista_t lista_msg;

	if ((st = validar_arg(argc, argv, &model_filename, &fmt, &output_filename)) != ST_OK)
	{
		handle_error(st);
		return EXIT_FAILURE;
	}

	if ((model_fp = fopen(model_filename, "rt")) == NULL)
	{
		handle_error(ST_UNABLE_TO_OPEN_FILE);
		free(model_filename);
		free(output_filename);
		return EXIT_FAILURE;
	}

	if ((output_fp = fopen_fmt(output_filename, fmt)) == NULL)
	{
		handle_error(ST_UNABLE_TO_OPEN_FILE);
		free(model_filename);
		free(output_filename);
		fclose(model_fp);
		return EXIT_FAILURE;
	}

	
	if ((st = lista_crear(&lista_msg)) != ST_OK)
	{
		handle_error(st);
		free(model_filename);
		free(output_filename);
		fclose(model_fp);
		fclose(output_fp);
		return EXIT_FAILURE;
	}
	/***********************
	PARTE DEL CODIGO PARA PROCESAR EL ARCHIVO
	**********************/
	
	if((st = crear_arreglo_sensores_modelo(&arr_sensores, &n_sensores, model_fp)) != ST_OK )
	{
		handle_error(st);
		free(model_filename);
		free(output_filename);
		fclose(model_fp);
		fclose(output_fp);
		return EXIT_FAILURE;
	}

	/***********************
	PARTE DEL CODIGO PARA HACER LA SIMULACIÓN
	mirar las funciones que arme generarmensaje y procesarmensaje
	**********************/

	srand(time(NULL));
	
	for (n_iteraciones = 0; n_iteraciones < CANT_ITERACIONES; n_iteraciones++)
	{
		cant_msg_generar = rand() % MAX_CANT_MSG_GENERAR_POR_ITERACION;
		if ((st = generar_mensajes(cant_msg_generar, &lista_msg, arr_sensores, n_sensores)) != ST_OK)
		{
			handle_error(st);
			free(model_filename);
			free(output_filename);
			lista_destruir(&lista_msg, &destruir_mensaje);
			destruir_arreglo_sensor(&arr_sensores, &n_sensores);
			fclose(model_fp);
			fclose(output_fp);
			return EXIT_FAILURE;
		}
		
		cant_msg_procesar = rand() % MAX_CANT_MSG_PROCESAR_POR_ITERACION;
		if ((st = procesar_mensajes(cant_msg_procesar, &lista_msg, fmt, output_fp)) != ST_OK)
		{
			switch(st)
			{
				case ST_LISTA_VACIA:
					continue;
				default:
					handle_error(st);
					free(model_filename);
					free(output_filename);
					lista_destruir(&lista_msg, &destruir_mensaje);
					destruir_arreglo_sensor(&arr_sensores, &n_sensores);
					fclose(model_fp);
					fclose(output_fp);
					return EXIT_FAILURE;
			}
		}
	}
	lista_destruir(&lista_msg, &destruir_mensaje);
	destruir_arreglo_sensor(&arr_sensores, &n_sensores);
	free(model_filename);
	free(output_filename);
	fclose(model_fp);
	fclose(output_fp);

	return EXIT_SUCCESS;
}



status_t validar_arg(int argc, const char *argv[], char **model_filename_ptr,formato_t *fmt , char **output_filename_ptr)
{
	int model_pos, fmt_pos, output_pos;

	if (argc > MAX_ARG)
	{
		return ST_INVALID_CANT_ARG;
	}

	model_pos = obtener_pos(PARAM_MODEL, argc, argv);
	fmt_pos = obtener_pos(PARAM_FORMAT, argc, argv);
	output_pos = obtener_pos(PARAM_FILE_MSG, argc, argv);

	if (model_pos == argc)
	{
		return ST_ARG_NOT_FOUND;
	}

	*model_filename_ptr= strdup(argv[model_pos]);
	*fmt = CSV; /*default*/
	if(fmt_pos != NO_PARAM)
	{
		if ((*fmt = str_to_fmt(argv[fmt_pos])) == CANT_FMT)
		{
			return ST_INVALID_ARG_FMT;
		}
	}

	if(output_pos != NO_PARAM)
	{
		*output_filename_ptr = strdup(argv[output_pos]);
	}
	else	*output_filename_ptr = strdup(STD_OUT_PARAM);
	
	return ST_OK;
}


int obtener_pos(const char *elem, int n_max_elem, const char *str_array[])
{
	int i;
	char *lower;

	for (i = 0; i < n_max_elem; i++)
	{
		if (!strcmp(elem, lower = tolower_str(str_array[i])))
		{
			free(lower);
			return (i + 1);
		}
		free(lower);
	}
	return NO_PARAM;
}

formato_t str_to_fmt(const char *str)
{
	int i;
	char *ftm_strings[] =
	{
		BIN_FMT_STR,
		CSV_FMT_STR
	};
	char *lower;
	for (i = 0; i < CANT_FMT; i++)
	{
		if(!strcmp(lower = tolower_str(str),ftm_strings[i]))
		{
			free(lower);
			return i;
		}
		free (lower);
	}
	return i;
}

FILE *fopen_fmt(const char *filename, formato_t fmt)
{
	if (!filename)
	{
		return NULL;
	}
	if(strcmp(filename, STD_OUT_PARAM) == 0)
	{
		return stdout;
	}
	switch(fmt)
	{
		case BIN:
			return fopen(filename,"wb");
		case CSV:
			return fopen(filename,"wt");
		default:
			return NULL;
	}
}

status_t split (char *s, char delim, size_t *cant_fields, char ***csvfields)
{
	char **aux;
	int i, j, k, n;


	if (!cant_fields || !csvfields)
	{
		return ST_NULL_POINTER;
	}

	if (s == NULL)
	{
		*cant_fields = 0;
		return ST_NULL_POINTER;
	}

	if((*csvfields = (char **)calloc(1, sizeof(char *))) == NULL)
	{
		*cant_fields = 0;
		return ST_NO_MEM;
	}

	n = 0;
	for (i = 0, j = 0, k = 0; s[i]; i++)
	{
		if (s[i] == delim)
		{
			s[i] = '\0';
			if(s[i + 1] != delim)
			{
				if((aux = (char **)realloc((*csvfields), (++n) * sizeof(char *))) == NULL)
				{
					free((*csvfields));
					*cant_fields = 0;
					return ST_NO_MEM;
				}
				(*csvfields) = aux;
				(*csvfields)[j] = strdup(&s[k]);
				j++;
				k = i + 1;
			}
		}
		else	if (s[i + 1] == '\0')
				{
					if((aux = (char **)realloc((*csvfields), (++n) * sizeof(char *))) == NULL)
						{
							free((*csvfields));
							*cant_fields = 0;
							return ST_NO_MEM;
						}
					(*csvfields) = aux;
					(*csvfields)[j] = strdup(&s[k]);
				}
	}
	*cant_fields = n;
	return ST_OK;
}

char* strdup (const char *str)
{
	char *str2;
	if((str2 = (char *)calloc(((strlen(str)) + 1), sizeof(char))) == NULL)
	{
		return NULL;
	}
	strcpy(str2, str);
	return str2;
}


status_t generar_mensajes(size_t n, lista_t *l, sensor_t **sens, size_t n_sens)
{
	size_t i, j;
	status_t st;
	for (i = 0; i < n; i++)
	{
		j = rand() % n_sens;
		if ((st = lista_insertar_final(l, SENSOR_adquirir_datos(sens[j]))) != ST_OK)
		{
			return st;
		}
	}
	return ST_OK;
}

status_t procesar_mensajes(size_t m, lista_t *l, formato_t fmt, FILE *fp)
{
	size_t i;
	status_t st;
	status_t (*fn[CANT_FUNC_PROC])(mensaje_t *, FILE *) =
	{
		procesar_mensaje_BIN,
		procesar_mensaje_CSV
	};

	for(i = 0; i < m; i++)
	{
		if(lista_esta_vacia(l))
		{
			return ST_LISTA_VACIA;
		}
		if((st = (fn[fmt])((*l)->dato, fp)) != ST_OK)
		{
			return st;
		}
		pop_lista(l, &destruir_mensaje);
	}
	return ST_OK;
}


status_t procesar_mensaje_BIN(mensaje_t *l, FILE *fp)
{
	char *lexem;
	char fin = SUFIX_END;

	if(!l || !fp)
	{
		return ST_NULL_POINTER;
	}

	lexem = strdup(PREFIX_LEXEM_CSV);
	if(fwrite(lexem, LEXEM_LENGTH, 1, fp) != 1)
	{
		free(lexem);
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}
	if(fwrite(&((l)->largo), sizeof((l)->largo) + sizeof((l)->id) + sizeof((l)->sub_id) , 1, fp) != 1)
	{
		free(lexem);
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}
	if(fwrite((l)->datos, sizeof(*((l)->datos)), (l)->largo, fp) != (l)->largo)
	{
		free(lexem);
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}
	if(fwrite(&fin, sizeof(fin), 1, fp) != 1)
	{
		free(lexem);
		return ST_UNABLE_TO_WRITE_ON_FILE;
	}
	free(lexem);
	return ST_OK;
}

status_t procesar_mensaje_CSV(mensaje_t *l, FILE *fp)
{
	char *lexem;
	size_t i;

	if (!l || !fp)
	{
		return ST_NULL_POINTER;
	}
	lexem = strdup(PREFIX_LEXEM_CSV);
	fprintf(fp, "%s%c%lu%c%u%c%i%c", lexem, CSV_DELIM, (l)->largo, CSV_DELIM, (l)->id, CSV_DELIM, (l)->sub_id, CSV_DELIM);

	for (i = 0; i < (l)->largo; i++)
	{
		fprintf(fp, "%u%c", ((l)->datos)[i], CSV_DELIM);
	}

	fprintf(fp, "%c\n", SUFIX_END);
	free(lexem);

	return ST_OK;
}

status_t leer_linea_modelo(FILE *srcf, char **line, bool_t *eof)
{
	char *aux, c;
	size_t alloc_size, used_size;

	if(line == NULL)
		return ST_NULL_POINTER;

	if (!srcf || !eof)
		return ST_NULL_POINTER;

	if(((*line) = (char*)calloc(INITSIZE + 1, sizeof(char))) == NULL)
		return ST_NO_MEM;

	if((c = fgetc(srcf)) == '\n')
	{
		free(*line);
		(*line) = NULL;
		return ST_OK;
	}

	if (c == COMMENT_CHAR)
	{
		while(((c = fgetc(srcf)) != '\n') && (c != EOF));
		free(*line);
		(*line) = NULL;
		return ST_OK;
	}

	if(c == EOF) 
	{
		free(*line);
		*eof = TRUE;
		(*line) = NULL;
		return ST_OK;
	}

	(*line)[0] = c;
	used_size = 1;
	alloc_size = INITSIZE;

	while(((c = fgetc(srcf)) != '\n') && (c != EOF))
	{
		if(used_size == alloc_size)
		{
			if((aux = (char *)realloc(*line, sizeof(char) * (alloc_size + CHOP_SIZE + 1))) == NULL)
			{
				free(*line);
				return ST_NO_MEM;
			}
			(*line) = aux;
			alloc_size += CHOP_SIZE;
		}

		(*line)[used_size] = c;
		used_size++;
	}
	(*line)[used_size] = '\0';

	return ST_OK;
}

status_t crear_arreglo_sensores_modelo(sensor_t ***arr_sensores, size_t *cant_sensores, FILE *ptrf_model)
{
	sensor_type_t id;
	int sub_id;
	char *model_line;
	bool_t eof;
	size_t cant, numparam;
	char **campos_model;
	double *parametros;
	sensor_t *sensor, **aux;
	status_t st;

	if(!arr_sensores || !cant_sensores)
	{
	return ST_NULL_POINTER;
	}
	*cant_sensores = 0;
	(*arr_sensores) = NULL;
	eof = FALSE;

	do
	{
		if((st = leer_linea_modelo(ptrf_model, &model_line, &eof) != ST_OK))
			return ST_ERROR_LEER_MODELO;

		if((model_line) == NULL)
		{
			continue;
		}

		if((st = split(model_line, DELIM, &cant, &campos_model)) != ST_OK)
		{
			free(model_line);
			return st;
		}
		free(model_line);

		if((st = obtener_id(campos_model[ID_POS], &id) != ST_OK))
		{
			liberar_campos(&campos_model, cant);
			return st;
		}
		if((st = obtener_subid(campos_model[SUB_ID_POS], &sub_id)) != ST_OK)
		{
			liberar_campos(&campos_model, cant);
			return st;
		}
		numparam = cant - 2;		
		if((st = obtener_params(campos_model, &parametros, numparam))!= ST_OK)
		{
			liberar_campos(&campos_model, cant);
			return st;
		}

		if((aux = (sensor_t **)realloc((*arr_sensores), (++(*cant_sensores)) * sizeof(sensor_t *))) == NULL)
		{
			liberar_campos(&campos_model, cant);
	    	destruir_arreglo_sensor(arr_sensores, cant_sensores);
	 		return ST_NO_MEM;
		}
		*arr_sensores = aux;

		switch(id)
		{
			case SENSOR_IMU:
				if((st = IMU_crear(&sensor, id, sub_id, parametros, numparam)) != ST_OK)
				{
				liberar_campos(&campos_model, cant);
				destruir_arreglo_sensor(arr_sensores,cant_sensores);
					return st;
				}
				break;

			case SENSOR_GPS:
				if((st = GPS_crear(&sensor, id, sub_id, parametros, numparam)) != ST_OK)
				{
					liberar_campos(&campos_model, cant);
					destruir_arreglo_sensor(arr_sensores,cant_sensores);
					return st;
				}
				break;

			case SENSOR_US:
				if((st = US_crear(&sensor, id, sub_id, parametros, numparam)) != ST_OK)
				{
					liberar_campos(&campos_model, cant);
					destruir_arreglo_sensor(arr_sensores,cant_sensores);
					return st;
				}
				break;
		}
		(*arr_sensores)[*cant_sensores - 1] = sensor;
		liberar_campos(&campos_model, cant);
		campos_model = NULL;     
	}
	while(eof == FALSE);
	return ST_OK;
}

void liberar_campos(char *** campos, size_t n)
{
	size_t i;
	if(!campos) return;
	if(!(*campos)) return;
	for (i = 0; i < n; i++)
	{
		free((*campos)[i]);
	}
	free(*campos);
}

status_t obtener_id(const char *id_string, sensor_type_t *id)
{
	if(!id || !id_string)
	{
		return ST_NULL_POINTER;
	}
	if(strcmp(id_string, IMU_ID) == 0)
	{
		*id = SENSOR_IMU;
		return ST_OK;
	}
	if(strcmp(id_string, GPS_ID) == 0)
	{
		*id = SENSOR_GPS;
		return ST_OK;
	}
	if(strcmp(id_string, US_ID) == 0)
	{
		*id = SENSOR_US;
		return ST_OK;
	}
	return ST_INVALID_ID;
}

status_t obtener_subid(const char *subid_string, int *sub_id)
{
	char* endptr;
	if(!subid_string || !sub_id)
	{
		return ST_NULL_POINTER;	
	}
	

	*sub_id = (int)strtod(subid_string, &endptr);
	if(*endptr != '\0')
	{
		return ST_INVALID_SUBID;	
	}
	return ST_OK;
}

status_t obtener_params(char **params_array, double **params, size_t cant)
{
	size_t i;
	char *endptr;

	if(!params_array || !params)
		return ST_NULL_POINTER;
	if((*params = (double *)calloc(cant, sizeof(double))) == NULL)
		return ST_NO_MEM;

	for(i = 0; i < cant; i++)
	{
		(*params)[i] = strtod(params_array[i + 2], &endptr);
		if(*endptr != '\0')
		{
			free(*params);
			*params = NULL;
			return ST_INVALID_PARAMS;
		}
	}
	return ST_OK;
}
void destruir_arreglo_sensor(sensor_t ***arr_sensores, size_t *cant_sensores)
{
	size_t i;

	if(!arr_sensores || !cant_sensores)
		return;

	for(i = 0; i < *cant_sensores; i++)
	{
		switch(((*arr_sensores)[i])->id)
		{
			case SENSOR_IMU:
				IMU_destruir(&((*arr_sensores)[i]));
				break;

			case SENSOR_GPS:
				GPS_destruir(&((*arr_sensores)[i]));
				break;

			case SENSOR_US:
				US_destruir(&((*arr_sensores)[i]));
				break;
		}
	}
	free(*arr_sensores);
	*arr_sensores = NULL;
	*cant_sensores = 0;
	return;
}

char *tolower_str(const char *str)
{
	char *strlow;
	size_t i;
	if ((strlow = (char *)calloc(strlen(str) + 1, sizeof(char))) == NULL)
	{
		return NULL;
	}
	for (i = 0; i < strlen(str); i++)
	{
		strlow[i] = tolower(str[i]);
	}
	strlow[i] = '\0';
	return strlow;
}

void destruir_mensaje(mensaje_t **msj)
{
	if((msj == NULL) || (*msj == NULL))
	{
		return;
	}
	free((*msj)->datos);
	((*msj)->datos) = NULL;
	free(*msj);
	*msj = NULL;
}
