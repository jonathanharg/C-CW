all: single byn

../2-Shuffling/riffle.o:
	$(MAKE) -C ../2-Shuffling/ riffle.o

.PHONY: ../2-Shuffling/riffle.o

beggar.o: beggar.c beggar.h
	gcc -ansi -c -O2 beggar.c

hand.o: hand.c hand.h
	gcc -ansi -c -O2 hand.c

single.o: single.c
	gcc -ansi -c -O2 single.c

single: single.o hand.o beggar.o ../2-Shuffling/riffle.o
	gcc -ansi -O2 single.o hand.o beggar.o ../2-Shuffling/riffle.o -o single

byn.o: byn.c
	gcc -ansi -c -O2 byn.c

byn: byn.o hand.o beggar.o ../2-Shuffling/riffle.o
	gcc -ansi -O2 byn.o hand.o beggar.o ../2-Shuffling/riffle.o -o byn

clean:
	rm *.o single byn
