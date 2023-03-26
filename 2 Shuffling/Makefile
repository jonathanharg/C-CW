all: quality demo_shuffle

riffle.o: riffle.c riffle.h
	gcc -ansi -c -O2 riffle.c

demo_shuffle.o: demo_shuffle.c
	gcc -ansi -c -O2 demo_shuffle.c

demo_shuffle: demo_shuffle.o riffle.o
	gcc -ansi -O2 demo_shuffle.o riffle.o -o demo_shuffle

quality.o: quality.c
	gcc -ansi -O2 -c quality.c

quality: quality.o riffle.o
	gcc -ansi -O2 quality.o riffle.o -o quality

clean:
	rm *.o demo_shuffle quality
