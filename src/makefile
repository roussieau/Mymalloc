myalloc : Main.o Mymalloc.o
	gcc -Wall -o Main Main.o Mymalloc.o
	./Main

Main.o: Main.c Mymalloc.h
	gcc -c Main.c

My_alloc.o: Mymalloc.c Mymalloc.h
	gcc -c My_alloc.c

clean:
	rm -rf *.o
