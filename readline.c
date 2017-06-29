#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


char* read_line (FILE*);

int main(){
	char* cadena;
	cadena=read_line(stdin);
	printf("%s\n",cadena);
	free(cadena);
}

status_t read_line (FILE* srcf,char** line, bool_t* eof){

	char *aux;
	int c;
	size_t alloc_size=INITSIZE, used_size=0;

	if(line==NULL){
		return ST_NULL_POINTER;
	}

	if (st=NULL){
		(*line)=NULL;
		return ST_NULL_POINTER;
	}

	if (FILE==NULL){
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
				*st=ST_NO_MEM;
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
		*st=ST_NO_MEM;
		free(*line);
		(*line)=NULL;
	}

	(*line)=aux;
	(*line)[used_size]='\0';

	return ST_OK;
}
