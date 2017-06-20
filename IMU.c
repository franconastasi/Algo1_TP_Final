#include <stdlib>
#include <time.h>
#include "types.h"
#include "sensor.h"



status_t IMU_crear(sensor_t** sens,sensor_type_t tpe, int sub_id, double* param_ptr){
	if (!sens || !param_ptr)
	{
		return ST_OK;
	}
	if ( (*sens = (sensor_t*)malloc(sizeof(sensor_t))) == NULL )
	{
		return ST_NO_MEM;
	}

	(*sens)->id = tpe;
	(*sens)->sub_id = sub_id;
	(*sens)->params = param_ptr
}

void IMU_destruir(sensor_t** sens){
	free( (*sens)->params );
	(*sens)->params = NULL;
	free(*sens );
	*sens = NULL;
}

mensaje_t* IMU_adquirir_datos(sensor_t* sens){
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
	/*Como largo es de tipo size_t y su representración depende de donde se lo está implementadndo
	supongo que tiene la menor implementación posible (osea char)
	*/
	mensaje->largo = (rand() % (sizeof(char)*8))
	
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