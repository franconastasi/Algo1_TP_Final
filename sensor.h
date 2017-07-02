#ifndef SENSOR__H
#define SENSOR__H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct sensor
{
	sensor_type_t id;
	int sub_id;
	mensaje_t* (*adquirir_datos)(struct sensor * sens);
	double* params;
} sensor_t;

status_t SENSOR_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void SENSOR_destruir(sensor_t **);
status_t SENSOR_set_adquisidora(sensor_t *, mensaje_t *(*fn)(sensor_t *));
mensaje_t *SENSOR_adquirir_datos(sensor_t *);

crear_arreglo_sensores_modelo(sensor_t ***, size_t *, FILE *);

#endif