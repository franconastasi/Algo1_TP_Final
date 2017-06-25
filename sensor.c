#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "cumunes.h"



status_t SENSOR_crear(sensor_t** sens,sensor_type_t tpe, int sub_id, double* param_ptr,size_t numparams){
	if (!sens || !param_ptr)
	{
		return ST_NULL_POINTER;
	}

	if ( (*sens = (sensor_t*)calloc(1,sizeof(sensor_t))) == NULL )
	{
		return ST_NO_MEM;
	}

	(*sens)->id = tpe;
	(*sens)->sub_id = sub_id;
	(*sens)->params = param_ptr;
	(*sens)->nparams = numparams;
	return ST_OK;
}

void SENSOR_destruir(sensor_t ** sens){
	if (!sens)
	{
		handleError(ST_NULL_POINTER);
	}
	free(  (*sens)->params);
	(*sens)->params = NULL;
	(*sens)->adquirir_datos = NULL;
	free(*sens):
	*sens = NULL;
}

status_t SENSOR_set_adquisidora(sensor_t* sens, mensaje_t* (*fn)(sensor_t*)){
	if(!sens || !fn){
		return ST_ILLEGAL;
	}
	sens->adquirir_datos = fn;
	return ST_OK;
}

mensaje_t* SENSOR_adquirir_datos(sensor_t* sens){
	if (!sens && !(sens->adquirir_datos))
	{
		return (sens->adquirir_datos)(sens);
	}else{
		return NULL;
	}

}
