#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum{
	ST_OK,
	ST_NO_MEM,
	ST_NULL_POINTER
} status_t;


char** split (const char *s, char delim, size_t *fields,status_t* st);
char* strdup (const char *str);

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
