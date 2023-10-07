CC=gcc
CFLAGS= -Werror -Wall
OBJS= MYps.o

.PHONY: all clean

all: Main

Main: $(OBJS)
	$(CC) -o Main $(OBJS) $(CFLAGS)


Run: Main
	./Main $(ARGS)	


Myps.o: MYps.c 
	$(CC) -c MYps.c -o MYps.o $(CFLAGS)

.PHONY: clean

clean: -rm Main $(OBJS)


	