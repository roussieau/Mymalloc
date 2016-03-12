#include <stdlib.h>
#include <stdio.h>
#include "My_alloc.h"

int main(int argc, const char *argv[])
{
	mymalloc(64);
	int *test = (int *)mymalloc(sizeof(int));
	*test = 42;
	printf("la valeur est : %d \n", *test);
	myfree(test);
	int *test2 = (int *)mymalloc(sizeof(int));
	printf("la valeur est : %d \n", *test2);
	myfree(test2);
	int *test3 = (int *)mycalloc(sizeof(int));
	printf("la valeur est : %d \n", *test3);
	
	return EXIT_SUCCESS;
} 
