#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include "types.h"
#include "sensor.h"
#include "GPS.h"


status_t GPS_crear(sensor_t **sens, sensor_type_t id, int sub_id, double *param_ptr, size_t numparams)
{
	status_t st;

	if((st= SENSOR_crear(sens, id, sub_id, param_ptr, numparams)) != ST_OK)
	{
		return st;
	}

	if((st = SENSOR_set_adquisidora(*sens, &GPS_adquirir_datos)) != ST_OK)
	{
		return st;
	}

	return st;
}

void GPS_destruir(sensor_t **sens)
{
	SENSOR_destruir(sens);
}

mensaje_t *GPS_adquirir_datos(sensor_t *sens)
{
	size_t i;
	mensaje_t *mensaje;
	sensor_type_t tipos_sensores_array[CANT_TIPOS_SENSORES] ={
		SENSOR_IMU,
		SENSOR_GPS,
		SENSOR_US
	};
	
	if((mensaje = (mensaje_t *)malloc(sizeof(mensaje_t))) == NULL)
		return NULL;

	mensaje->id = tipos_sensores_array[sens->id];
	mensaje->sub_id = sens->sub_id;

	mensaje->largo = (rand() % MAX_CANT_DATOS);

	if((mensaje->datos = (uchar *)malloc(sizeof(uchar) * mensaje->largo)) == NULL)
	{
		free(mensaje);
		return NULL;
	}

	for (i = 0; i < mensaje->largo; i++)
	{
		(mensaje->datos)[i] = (rand() % MAX_VALOR_DATO);
	}
	return mensaje;
}
