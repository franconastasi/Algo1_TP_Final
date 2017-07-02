#include <stdio.h>
#include <stddef.h>
#include "types.h"
#include "comunes.h"
#include "config.h"
#include "language.h"


void handleError(status_t st)
{
	char *msg[] = 
	{
		MSG_NO_MEM,
		MSG_NULL_POINTER
	};
	fprintf(stderr, "%s %s\n", MSG_ERROR_PREFIX, msg[st-1]);
}