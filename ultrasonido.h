#ifndef ULTRASONIDO__H
#define ULTRASONIDO__H

#include "comunes.h"
#include "types.h"
#include "sensor.h"

status_t US_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void US_destruir(sensor_t **);
mensaje_t* US_adquirir_datos(sensor_t*);

#endif