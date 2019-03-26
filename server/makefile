CC      := gcc

LIBS    := zmq

LIB_DIR := /usr/local/bin
LIB_INC := /usr/local/include

provider_source := provider.c

.PHONY := clean

all: provider

provider: $(provider_source)
	$(CC) $^ -o $@ $(addprefix -l, $(LIBS)) $(addprefix -I, $(LIB_INC)) $(addprefix -L, $(LIB_DIR))

clean:
	rm -f provider