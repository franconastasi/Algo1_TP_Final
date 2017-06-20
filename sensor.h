#ifndef SENSOR__H
#define SENSOR__H

#include "types.h"

/* Borrar este comentario a lo último, lo dejo para que sublime autocomplete
	ST_SUCCESS,
	ST_ILLEGAL,
	ST_NO_SPACE
*/

typedef struct{
	sensor_type_t id,
	int sub_id,
	mensaje_t* (*adquirir_datos)(sensor_t * sens),
	double* params
}sensor_t;

status_t SENSOR_crear(sensor_t **);
void SENSOR_destruir(sensor_t **);
status_t SENSOR_set_adquisidora(sensort_t*, mensaje_t* (*fn)(sensor_t*));
mensaje_t* SENSOR_adquirir_datos(sensor_t*);


/*REVISAR SENSOR_CREAR Y SENSOR_DESTRUIR:
	SENSOR_CREAR TIENE EL PROBLEMA QUE HAY QUE ASIGNARLE LA FUNCIÓN DEPENDIENDO DEL ID
	PERO EN ESTE ARCHIVO SOLO TRAES TYPES.H, NO TRAES NINGUNO DE LOS .H (US.H,IMU.H,GPS.H)
	PORQUE ESTOS .H TRAEN SENSOR.H, ENTONCES PUEDE CAER EN UN LOOP

	CON SENSOR_DESTRUIR PASA ALGO PARECIDO PORQUE NECESITAMOS US_DESTRUIR O IMU_DESTRUIR QUE
	ESTÁN EN LOS .H
*/ 

status_t SENSOR_crear(sensor_t** sens){
	
	mensaje_t* (*fn[3])(sensor_t*) = { IMU_adquirir_datos, GPS_adquirir_datos, US_adquirir_datos }

	if (!sens){ 
		return ST_ILLEGAL
	}

	(*sens)->SENSOR_adquirir_datos = fn[ (*sens)-> ]




}

void SENSOR_destruir(sensor_t ** sens){

}

status_t SENSOR_set_adquisidora(sensor_t* sens, mensaje_t* (*fn)(sensor_t*)){
	if(!sens || !fn){
		return ST_ILLEGAL;
	}
	sens->adquirir_datos = fn;
	return ST_SUCCESS;
}

mensaje_t* SENSOR_adquirir_datos(sensor_t* sens){
	if (!sens && !(sens->adquirir_datos))
	{
		return (sens->adquirir_datos)(sens);
	}else{
		return NULL;
	}

}



#endif