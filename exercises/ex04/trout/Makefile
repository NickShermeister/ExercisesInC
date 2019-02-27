all: trout.o util.o

trout.o: trout.h trout.c util.c util.h main.c
	gcc -g -Wall -c trout.c util.c

util.o: util.h util.c
	gcc -g -Wall -c util.c
