test : Mymalloc.o test.o
	gcc -Wall -o Test Mymalloc.o test.o -lcunit
	./test 20
	make clean

Mymalloc.o: Mymalloc.c Mymalloc.h
	gcc -c Mymalloc.c

test.o: test.c Mymalloc.h
	gcc -Wall -c test.c

clean:
	rm -rf *.o
