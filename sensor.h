#ifndef SENSOR__H
#define SENSOR__H

#include "types.h"

typedef struct{
	sensor_type_t id,
	int sub_id,
	mensaje_t* (*adquirir_datos)(sensor_t * sens),
	double* params
}sensor_t;

status_t SENSOR_crear(sensor_t **,sensor_type_t, int , double* ,size_t);
void SENSOR_destruir(sensor_t **);
status_t SENSOR_set_adquisidora(sensort_t*, mensaje_t* (*fn)(sensor_t*));
mensaje_t* SENSOR_adquirir_datos(sensor_t*);

#endif
