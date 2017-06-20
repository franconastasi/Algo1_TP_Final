#ifndef ULTRASONIDO__H
#define ULTRASONIDO__H

/* Borrar este comentario a lo último, lo dejo para que sublime autocomplete
	ST_SUCCESS,
	ST_ILLEGAL,
	ST_NO_MEM
*/


#include "types.h"
#include "sensor.h"

status_t US_crear(sensor_t **,sensor_type_t,int,double*);
void US_destruir(sensor_t **);
mensaje_t* US_adquirir_datos(sensor_t*);


#endif