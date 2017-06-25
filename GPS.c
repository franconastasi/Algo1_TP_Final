#include <stdlib>
#include <time.h>
#include "types.h"
#include "sensor.h"



status_t GPS_crear(sensor_t** sens,sensor_type_t id, int sub_id, double* param_ptr ){
	status_t st;

	if ( (st= SENSOR_crear(sens,id,sub_id,*param_ptr)) != ST_OK )
	{
		return st;
	}

	if (  (st = SENSOR_set_adquisidora(*sens, &GPS_adquirir_datos )) != ST_OK )
	{
		return st;
	}
}

void GPS_destruir(sensor_t** sens){
	SENSOR_destruir(sens);
}

mensaje_t* GPS_adquirir_datos(sensor_t* sens){
	/* Hay que preguntar si esta función tiene que
	llevar un parámetro más: status_t st para notificar si hubo un error*/
	mensaje_t* mensaje;
	srand(time(NULL));
	size_t i;

	mensaje = (mensaje_t*)malloc(sizeof(mensaje_t));
	/*según tutorials point rand() devuelve un número entre 0 y MAX,
	 donde MAX depende de la implementación pero generalmente es 2^(15) -1 )
	 */
	mensaje->id=rand();
	mensaje->sub_id=rand();
	/*Como largo es size_t puede representar hasta un máximo de sizeof(size_t)*8 bits*/
	mensaje->largo = (rand() % (sizeof(size_t)*8))

	/*Se podría agregar los parámetros en el cálculo de los datos para que parezca mas real
	aunque no debería cambiar en nada la simulación
	*/
	mensaje_t->datos = (uchar*)malloc(sizeof(uchar)*mensaje->largo);
	for (i = 0; i < mensaje->largo; ++i)
	{
		mensaje_t->datos[i] = (rand() % (sizeof(uchar)*8))
	}
	return mensaje;

}