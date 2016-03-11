#include <stdlib.h>
#include <stdio.h>
#include "My_alloc.h"

int main(int argc, const char *argv[])
{
	myalloc(64);
	int *test = (int *)myalloc(sizeof(int));
	*test = 42;
	printf("la valeur est : %d \n", *test);
} 
