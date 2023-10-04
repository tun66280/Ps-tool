CC=gcc
CFLAGS= -Werror -Wall
OBJS= MYps.o

Main: $(OBJS)
	$(CC) -o Main $(OBJS) $(CFLAGS)


Myps.o: MYps.c 
	$(CC) -c MYps.c -o MYps.o $(CFLAGS)

.PHONY: clean

clean: -rm Main $(OBJS)


	