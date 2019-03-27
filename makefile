.PHONY: clean server

all: server

server:
	make -C $@

clean:
	make $@ -C server
