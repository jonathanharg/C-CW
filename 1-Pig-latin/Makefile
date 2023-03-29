all: piglatin test_pig

piglatin: pig.o piglatin.o
	gcc -ansi -O2 pig.o piglatin.o -o piglatin

piglatin.o: piglatin.c
	gcc -ansi -O2 -c piglatin.c

test_pig: pig.o test_pig.o
	gcc -ansi -O2 test_pig.o pig.o -o test_pig

test_pig.o: test_pig.c
	gcc -ansi -O2 -c test_pig.c

pig.o: pig.h pig.c
	gcc -ansi -O2 -c pig.c

clean:
	rm *.o test_pig piglatin
