#ifndef GPS__H
#define GPS__H

/* Borrar este comentario a lo último, lo dejo para que sublime autocomplete
	ST_SUCCESS,
	ST_ILLEGAL,
	ST_NO_SPACE
*/


#include "types.h"
#include "sensor.h"


status_t GPS_crear(sensor_t **,sensor_type_t,int,double*);
void GPS_destruir(sensor_t **);
mensaje_t* GPS_adquirir_datos(sensor_t*);

#endif