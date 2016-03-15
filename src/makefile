myalloc : Main.o Mymalloc.o
	gcc -Wall -o Main Main.o Mymalloc.o
	./Main

test : Mymalloc.o test.o
	gcc -Wall -o Test Mymalloc.o test.o -lcunit
	./test
	make clean

Main.o: Main.c Mymalloc.h
	gcc -c Main.c

Mymalloc.o: Mymalloc.c Mymalloc.h
	gcc -c Mymalloc.c

test.o: test.c Mymalloc.h
	gcc -Wall -c test.c

clean:
	rm -rf *.o
