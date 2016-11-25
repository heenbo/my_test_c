CROSS_COMPILE = 
CC = gcc


SERVER_SOURCE = server.c 
CLIENT_SOURCE = client.c
SOURCE = $(SERVER_SOURCE) $(CLIENT_SOURCE)

SERVER_PROJECT := $(addsuffix .o,$(basename ${SERVER_SOURCE}))
CLIENT_PROJECT := $(addsuffix .o,$(basename ${CLIENT_SOURCE}))
PROJECT := $(addsuffix .o,$(basename ${SOURCE}))

SERVER_OBJECT = server
CLIENT_OBJECT = client 
OBJECT = $(SERVER_OBJECT) $(CLIENT_OBJECT)

CFLAGS = -Wall -g -O0 -I./include 
LDFLAGS = 

all : $(OBJECT)

$(OBJECT) : $(PROJECT)
	${CROSS_COMPILE}${CC} $(SERVER_PROJECT) -o $(SERVER_OBJECT) ${LDFLAGS}
	${CROSS_COMPILE}${CC} $(CLIENT_PROJECT) -o $(CLIENT_OBJECT) ${LDFLAGS}

$(PROJECT) : $(SOURCE)
	${CROSS_COMPILE}${CC} -c $^ ${CFLAGS}

clean : 
	-rm -f $(PROJECT) $(OBJECT) *.o
