#ifndef TYPES__H
#define TYPES__H

typedef unsigned char uchar;


typedef struct {
	size_t largo;
	int id, sub_id;
	uchar * datos;
}mensaje_t;


typedef enum{
	SENSOR_IMU,
	SENSOR_GPS,
	SENSOR_US
}sensor_type_t;

typedef enum {
	FALSE;
	TRUE;
}bool_t;


typedef enum {
	ST_OK,
	ST_NO_MEM,
	ST_NULL_POINTER,
	ST_UNABLE_TO_WRITE_ON_FILE,
	ST_UNABLE_TO_READ_FROM_FILE,
	ST_INVALID_CANT_ARG,
	ST_ARG_NOT_FOUND,
	ST_INVALID_ARG_FMT,
	ST_UNABLE_TO_OPEN_FILE,
	ST_INVALID_SUBID,
	ST_INVALID_ID,
	ST_INVALID_PARAMS,
	ST_ERROR_LEER_MODELO,
}status_t;

typedef enum{
	BIN,
	CSV
}formato_t;

#endif
