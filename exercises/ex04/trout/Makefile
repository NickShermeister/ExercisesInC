all: trout.o util.o main.o

trout.o: trout.h trout.c util.c util.h main.c
	gcc -g -Wall -c trout.c util.c

util.o: util.h util.c
	gcc -g -Wall -c util.c

main.o: util.h trout.h main.c
	gcc -c -Wall main.c

trout: trout.o util.o main.o
	gcc -Wall -o trout trout.o util.o main.o
