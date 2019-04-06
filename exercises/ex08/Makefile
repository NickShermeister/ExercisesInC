all: main

main: ex_compile.o word_count.o
	gcc `pkg-config --cflags --libs glib-2.0` ex_compile.o -o main -lm `pkg-config --cflags --libs glib-2.0`
	gcc `pkg-config --cflags --libs glib-2.0` word_count.o -o word_count -lm `pkg-config --cflags --libs glib-2.0`

ex_compile.o: ex_compile.c
	gcc ex_compile.c `pkg-config --cflags --libs glib-2.0` -c

word_count.o: word_count.c
	gcc word_count.c `pkg-config --cflags --libs glib-2.0` -c
