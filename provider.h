#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "zmq.h"

#define MAX_THOUGHT_LEN          (4096)
#define MAX_THOUGHTS_HERE        (10000)

#define PROVIDER_IPC_SOCKET      "ipc:///tmp/provider_ipc"

typedef struct strings_t {
	int size;
	char **buffer;
} strings_t;