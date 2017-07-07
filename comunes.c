#include <stdio.h>
#include <stddef.h>
#include "types.h"
#include "comunes.h"
#include "config.h"
#include "language.h"


void handle_error(status_t st)
{
	char *msg[] = 
	{
		MSG_NO_MEM,
		MSG_NULL_POINTER,
		MSG_NULL_POINTER,
		MSG_UNABLE_TO_WRITE_ON_FILE,
		MSG_UNABLE_TO_READ_FROM_FILE,
		MSG_INVALID_CANT_ARG,
		MSG_ARG_NOT_FOUND,
		MSG_INVALID_ARG_FMT,
		MSG_UNABLE_TO_OPEN_FILE,
		MSG_INVALID_SUBID,
		MSG_INVALID_ID,
		MSG_INVALID_PARAMS,
		MSG_ERROR_READ_MODEL
	};
	fprintf(stderr, "%s: %s\n", MSG_ERROR_PREFIX, msg[st-1]);
}