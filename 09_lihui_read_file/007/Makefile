CROSS_COMPILE = 
CC = gcc

SOURCE = main.c
PROJECT = main.o

OBJECT = analysis

CFLAGS = -Wall -g -O0 -I./include 
LDFLAGS = 

all : $(OBJECT)

$(OBJECT) : $(PROJECT)
	${CROSS_COMPILE}${CC} $^ -o $@ ${LDFLAGS}

$(PROJECT) : $(SOURCE)
	${CROSS_COMPILE}${CC} -c $^ ${CFLAGS}

clean : 
	-rm -f $(PROJECT) $(OBJECT) *.o
