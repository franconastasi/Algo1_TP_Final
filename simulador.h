#ifndef SIMULADOR__H
#define SIMULADOR__H

#define CANT_ARG 7

#define PARAM_MODEL "--mdl"
#define PARAM_FORMAT "--fmt"
#define PARAM_FILE_MSG "--out"

#define STD_OUT_PARAM "-"
#define CANT_FUNC_PROC 2

/*#define PREFIX_LEXEM {'H','O','U','S','E'}*/
#define SUFIX_END 'D'
#define CSV_DELIM ','

#define CANT_FMT 2
#define BIN_FMT_STR "bin"
#define CSV_FMT_STR "csv"



status_t split (const char *, char, size_t *,char***);
char* strdup (const char *str);

status_t generarMensajes(size_t n, lista_t* l,sensor_t ** sens);
status_t procesarMensajes(size_t m, lista_t* l);
status_t procesarMensajeBIN(lista_t* l, FILE* fp);
status_t procesarMensajeCSV(lista_t* l, FILE* fp);

status_t validar_cant_argumentos(int);
status_t validar_arg(int argc, const char* argv[], char* model_filename, *formato_t ftm ,char* output_filename);
int obtener_pos(char* elem,int n_max_elem, char* str_array[])
formato_t str_to_ftm(char * str);

FILE* fopen_fmt(char* filename, formato_t fmt);



#endif
