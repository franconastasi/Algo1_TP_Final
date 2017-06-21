#ifndef TYPES__H
#define TYPES__H


typedef struct {
	int id, sub_id;
	size_t largo;
	unsigned char * datos;
}mensaje_t;


typedef enum{
	SENSOR_IMU,
	SENSOR_GPS,
	SENSOR US
}sensor_type_t;

typedef enum {
	FALSE;
	TRUE;
}bool_t;


typedef enum {
	ST_OK,
	ST_NO_MEM,
	ST_NULL_POINTER
}status_t;

typedef unsigned char uchar;

typedef enum{
	BIN,
	CSV
}formato_t;

#endif
