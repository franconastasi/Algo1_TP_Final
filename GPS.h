#ifndef GPS__H
#define GPS__H


#include "comunes.h"
#include "types.h"
#include "sensor.h"


status_t GPS_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void GPS_destruir(sensor_t **);
mensaje_t *GPS_adquirir_datos(void);

#endif