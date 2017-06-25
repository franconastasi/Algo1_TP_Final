#include "types"
#include <stdio.h>
#include <stdlib.h>
#include "cumunes.h"


bool_t lista_esta_vacia(const lista_t *ptr){
	return (*ptr == NULL) ? TRUE : FALSE;
}

status_t lista_crear(lista_t *pl){
	if(!pl){
		return ST_ILLEGAl;
	}

	*pl = NULL;
	return ST_OK;
}

status_t lista_crear_nodo(nodo_t** nodo, void* dato){

	if (!nodo){
		return ST_ILLEGAL;
	}
	if((*nodo = (nodo_t*)malloc(sizeof(nodo_t) )) == NULL ){
		return ST_NO_MEM;
	}
	(*nodo)->sig = NULL;
	(*nodo)->dato = dato;
	return ST_OK;
}

void lista_destruir_nodo(nodo_t** nodo, void (*destruir_nodo)(void*)){
	if(lista_esta_vacia (nodo)){
		return
	}
	if (destruir_nodo != NULL)
	{
		*destruir_nodo((*nodo)->dato);
	}
	(*nodo)->dato = NULL;
	(*nodo)->sig = NULL
	free(*nodo);
	*nodo = NULL;
}

void lista_destruir(list_t* pl, void (*destruir_nodo)(void*)){
	nodo_t *aux;
	while(*pl){
		aux = *pl;
		*pl = (*pl)->sig
		lista_destruir_nodo(&aux, destruir_nodo);
	}
}


status_t lista_insertar_final(lista_t* pl, void* dato){
	nodo_t* aux, last;
	status_t st;
	if (!pl)
	{
		return ST_ILLEGAL;
	}
	if( (st = lista_crear_nodo(&aux,dato)) != ST_OK ){
		return st;
	}

	if (lista_esta_vacia(pl))
	{
		*pl = aux;
	}else{
		last = *pl;
		while(last->sig){
			last = last->sig;
		}	
		last->sig = aux;
	}
	return ST_OK;
}




















