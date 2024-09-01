SRC = server.c client.c
OBJ = server client
GCC = gcc

all: server client

server: server.c
	$(GCC) -o server server.c

client: client.c
	$(GCC) -o client client.c

clean: 
	rm -f $(OBJ)

re: clean all

.PHONY: all server client clean re
