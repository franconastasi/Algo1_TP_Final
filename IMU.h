#ifndef IMU__H
#define IMU__H

#include "comunes.h"
#include "types.h"
#include "sensor.h"



status_t IMU_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void IMU_destruir(sensor_t **);
mensaje_t *IMU_adquirir_datos(sensor_t*);

#endif