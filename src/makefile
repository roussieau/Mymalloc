myalloc : Main.o My_alloc.o
	gcc -Wall -o Main Main.o My_alloc.o

Main.o: Main.c My_alloc.h
	gcc -c Main.c

My_alloc.o: My_alloc.c My_alloc.h
	gcc -c My_alloc.c

clean:
	rm -rf *.o
