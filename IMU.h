#ifndef IMU__H
#define IMU__H

#include "types.h"
#include "sensor.h"

/* Borrar este comentario a lo último, lo dejo para que sublime autocomplete
	ST_SUCCESS,
	ST_ILLEGAL,
	ST_NO_SPACE
*/


status_t IMU_crear(sensor_t **, sensor_type_t, int, double *, size_t);
void IMU_destruir(sensor_t **);
mensaje_t *IMU_adquirir_datos(sensor_t *);

#endif