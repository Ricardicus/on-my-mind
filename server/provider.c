#include "provider.h"

/*
* Will post quotes to a local ipc socket
*/

void free_allocated_strings_t(strings_t **strings_p)
{
	free((*strings_p)->buffer);
	free(*strings_p);
	*strings_p = NULL;
}

strings_t* read_and_get_thoughts(const char* file)
{
	FILE *fp;
	strings_t *strings;
	char buffer[MAX_THOUGHT_LEN];

	fp = fopen(file, "r");

	if ( fp == NULL ) {
		fprintf(stderr, "%s.%d error: Unable to open file '%s'.\n", __FILE__, __LINE__, file);
		exit(1);
	}

	strings = calloc(1, sizeof(strings_t));
	if ( strings == NULL ) {
		fprintf(stderr, "%s.%d error: Unable to allocate memory.\n", __FILE__, __LINE__);
		exit(1);
	}

	strings->buffer = calloc( MAX_THOUGHTS_HERE , sizeof(char*));
	if ( strings->buffer == NULL ) {
		fprintf(stderr, "%s.%d error: Unable to allocate memory.\n", __FILE__, __LINE__);
		exit(1);
	}

	strings->size = 0; 

	memset(buffer, 0, sizeof(buffer));

	while ( fgets(buffer, sizeof(buffer), fp) != NULL ) {
		size_t quote_length = strlen(buffer);
		char *c;
		char *string = calloc(quote_length+1, 1);

		if ( string == NULL ) {
			fprintf(stderr, "%s.%d error: Unable to allocate memory.\n", __FILE__, __LINE__);
			exit(1);
		}

		memcpy(string, buffer, quote_length);

		c = strchr(string, '\n');
		if ( c == NULL ) {
			*c = 0;
		}

		strings->buffer[strings->size] = string;
		strings->size += 1;
	}

	fclose(fp);

	return strings;
}

void usage(const char *argv0)
{
	fprintf(stderr, "usage: %s file\n", argv0);
	exit(1);
}

int main(int argc, char *argv[])
{
	strings_t *strings;
	size_t n = 0;
	void *zmq_context;
	void *provider_socket;
	int rc;
	int error;

	if ( argc < 2 ) {
		usage(argv[0]);
	}

	strings = read_and_get_thoughts(argv[1]);

	while ( n < strings->size ) {
		printf("[%zu]: %s", n, strings->buffer[n]);
		++n;
	}

	zmq_context = zmq_ctx_new();
	provider_socket = zmq_socket(zmq_context, ZMQ_PUB);
	rc = zmq_bind(provider_socket, PROVIDER_IPC_SOCKET);
	if ( rc != 0 ) {
		error = errno;

 		fprintf(stderr, "%s.%d error: Failed to bind socket '%s'.\n", __FILE__, __LINE__, PROVIDER_IPC_SOCKET);
		switch (error ){
		case EINVAL: printf("EINVAL\n"); break;
		case EPROTONOSUPPORT: printf("EPROTONOSUPPORT\n"); break;
		case ENOCOMPATPROTO: printf("ENOCOMPATPROTO\n"); break;
		case EADDRINUSE: printf("EADDRINUSE\n"); break;
		case EADDRNOTAVAIL: printf("EADDRNOTAVAIL\n"); break;
		case ENODEV: printf("ENODEV\n"); break;
		case ETERM: printf("ETERM\n"); break;
		case ENOTSOCK: printf("ENOTSOCK\n"); break;
		case EMTHREAD: printf("EMTHREAD\n"); break;
		default: break;
		}

		exit(1);		
	}

	n = 0;
	while ( 1 ) {
		zmq_send (provider_socket, strings->buffer[n], strlen(strings->buffer[n]), 0);
		sleep(1);
		n = (n+1) % strings->size;
	}

	free_allocated_strings_t(&strings);

	return 0;
}