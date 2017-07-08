#ifndef SENSOR__H
#define SENSOR__H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define CANT_TIPOS_SENSORES 3

typedef struct sensor
{
	sensor_type_t id;
	int sub_id;
	mensaje_t* (*adquirir_datos)(struct sensor*);
	double* params;
	size_t nparams;
}sensor_t;

status_t SENSOR_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void SENSOR_destruir(sensor_t **);
status_t SENSOR_set_adquisidora(sensor_t *, mensaje_t *(*fn)(sensor_t*));
mensaje_t *SENSOR_adquirir_datos(sensor_t *);

#endif
