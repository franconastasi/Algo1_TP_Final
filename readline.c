#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line (FILE*);

int main(){
	char* cadena;
	cadena=read_line(stdin);
	printf("%s\n",cadena);
	free(cadena);
}

char* read_line (FILE* srcf,status_t *st){


	char* line;
	char *aux;
	int c;
	size_t alloc_size=INITSIZE, used_size=0;

	if (st=NULL){
		return NULL;
	}

	if (FILE==NULL){
		*st=ST_NULL_POINTER;
	}


	if((line=(char*)calloc(INITSIZE,sizeof(char)))==NULL){
		*st=ST_NO_MEM;
		return NULL;
	}

	if((c=fgetc(srcf))=='\n'){
		line[size]='\0';
		return line;
	}

	line[used_size]=c;
	used_size++;

	while(((c=fgetc(srcf)) != '\n') && (c != EOF)) {
		if(used_size==alloc_size){
			if((aux=(char*)realloc(line,sizeof(char)*(alloc_size+CHOP_SIZE)))==NULL){
				*st=ST_NO_MEM;
				free(line);
				return NULL;
			}
		}
		line=aux;
		line[size]=c;
		used_size++;
		alloc_size+=CHOP_SIZE;
	}


	size++;
	if((aux=(char*)realloc(line,sizeof(char)*1+size))==NULL){
		*st=ST_NO_MEM;
		free(line);
		return NULL;
	}
	line=aux;
	line[size]='\0';

	return line;
}
