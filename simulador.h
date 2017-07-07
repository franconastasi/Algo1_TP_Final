#ifndef SIMULADOR__H
#define SIMULADOR__H

#define MAX_ARG 7

#define PARAM_MODEL "--mdl"
#define PARAM_FORMAT "--fmt"
#define PARAM_FILE_MSG "--out"

#define CHOP_SIZE 30
#define INITSIZE 50

#define COMMENT_CHAR '#'
#define DELIM ' '

#define ID_POS 0
#define SUB_ID_POS 1

#define STD_OUT_PARAM "-"
#define CANT_FUNC_PROC 2

#define LEXEM_LENGTH 5
#define PREFIX_LEXEM_CSV "HOUSE"
#define SUFIX_END 'D'
#define CSV_DELIM ','

#define CANT_FMT 2
#define BIN_FMT_STR "bin"
#define CSV_FMT_STR "csv"
#define NO_PARAM -1


#define CANT_ITERACIONES 10
#define MAX_CANT_MSG_GENERAR_POR_ITERACION 50
#define MAX_CANT_MSG_PROCESAR_POR_ITERACION 50
#define MAX_CANT_DATOS 32
#define MAX_VALOR_DATO 100

#define IMU_ID "IMU"
#define US_ID "US"
#define GPS_ID "GPS"


#include <stdlib.h>
#include "lista.h"
#include "types.h"

status_t split(char *, char, size_t *, char ***);
char *strdup(const char *);
char *tolower_str(const char *);

status_t generar_mensajes(size_t , lista_t *, sensor_t **, size_t);
status_t procesar_mensajes(size_t , lista_t *, formato_t, FILE *);
status_t procesar_mensaje_BIN(mensaje_t *, FILE *);
status_t procesar_mensaje_CSV(mensaje_t *, FILE *);

status_t crear_arreglo_sensores_modelo(sensor_t ***, size_t *, FILE *);
void destruir_arreglo_sensor(sensor_t ***, size_t *);
status_t validar_cant_argumentos(int);
status_t validar_arg(int argc, const char **, char **, formato_t *, char **);
int obtener_pos(const char *, int , const char **);
formato_t str_to_fmt(const char *);

status_t obtener_id(const char *, sensor_type_t *);
status_t obtener_subid(const char *, int *);
status_t obtener_params(char **, double **, size_t );
status_t leer_linea_modelo(FILE *, char **, bool_t *);
void liberar_campos(char ***, size_t);

void destruir_mensaje(mensaje_t **);

FILE *fopen_fmt(const char *, formato_t);

#endif