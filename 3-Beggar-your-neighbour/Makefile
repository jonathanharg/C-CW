all: beggar

../2-Shuffling/riffle.o:
	$(MAKE) -C ../2-Shuffling/ riffle.o

# See https://stackoverflow.com/questions/27886570/is-it-possible-to-add-a-dependency-to-another-makefile
# Credit to Wintermute (StackOverflow)
.PHONY: ../2-Shuffling/riffle.o

beggar.o: beggar.c beggar.h
	gcc -ansi -c -O2 beggar.c beggar.h

beggar: beggar.o ../2-Shuffling/riffle.o
	gcc -ansi -O2 beggar.o -o beggar

clean:
	rm *.o *.gch beggar
