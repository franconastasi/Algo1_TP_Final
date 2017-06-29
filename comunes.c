#include <stdio.h>
#include "types.h"
#include <stddef.h>


void handleError(status_t st){
	char *msg[] = {
		MSG_NO_MEM,
		MSG_NULL_POINTER
	};
	fprintf(stderr, "%s %s\n",MSG_ERROR_PREFIX, msg[st-1] );
}
