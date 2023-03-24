riffle.o: riffle.c riffle.h
	gcc -ansi -c riffle.c

demo_shuffle.o: demo_shuffle.c
	gcc -ansi -c demo_shuffle.c

demo_shuffle: demo_shuffle.o riffle.o
	gcc -ansi demo_shuffle.o riffle.o -o demo_shuffle

clean:
	rm *.o demo_shuffle
