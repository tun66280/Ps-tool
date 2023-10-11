CC=gcc
CFLAGS= -Werror -Wall
OBJS= MYps.o

.PHONY: all clean

#Anim Ohene
# This makefile updates and recompiles MYps.c, and can run the program
all: Main

Main: $(OBJS)
	$(CC) -o Main $(OBJS) $(CFLAGS)


Run: Main
	./Main $(ARGS)	


Myps.o: MYps.c 
	$(CC) -c MYps.c -o MYps.o $(CFLAGS)


clean: -rm Main $(OBJS)


	