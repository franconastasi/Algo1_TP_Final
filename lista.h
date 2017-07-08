#ifndef LISTA__H
#define LISTA__H

#include "types.h"

typedef struct nodo
{
	struct nodo *sig;
	void *dato;
} nodo_t, *lista_t;

bool_t lista_esta_vacia(const lista_t *ptr);
status_t lista_crear(lista_t *pl);
status_t lista_crear_nodo(nodo_t **nodo, void *dato);
void lista_destruir_nodo(nodo_t **nodo, void (*destruir_dato)(void *));
void lista_destruir(lista_t *pl, void (*destruir_dato)(void *));
status_t lista_insertar_final(lista_t *pl, void *dato);
void pop_lista(lista_t *, void (*destruir_dato)(void *));

#endif
