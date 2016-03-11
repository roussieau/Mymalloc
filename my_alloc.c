#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

typedef struct block_header {
	unsigned int size : 29;
	unsigned int zero : 2;
	unsigned int alloc : 1;
} header;

header *first = NULL;
size_t *end = NULL;//Fin du heap

//aligne la taille sur 32 bits
//len est en byte
size_t calcul(size_t len)
{
	return len % 4 == 0 ? len : len + 4 - (len % 4);
}

void insert(header *start, int count, size_t size)
{
	start->size = size;
	start->zero = 0;
	start->alloc = 1;

	if((size_t)count == size+4)
		return;

	size_t reste = (size_t) count - size - 8;
	start += size/4 + 1;
	start->size = reste;
	start->zero = 0;
	start->alloc = 0;
}

//La taille size est en byte
void *myalloc(size_t size)
{
	size = calcul(size); // On aligne sur 32 bits
	if(first == NULL) //Lors du premier appel, on initialise le heap 
	{
		first = (header *)sbrk(size);
		end = sbrk(0);
		first->size = size;
		first->zero = 0;
		first->alloc = 0;
		return (void *) first;
	}
	//Navigation dans le heap
	header *nav = first;
	int count = 0;
	header *start = NULL;
	while((size_t *)nav < end)
	{
		if(count == 0)
		{
			start = nav;
		}
		if(nav->alloc == 1) //Le block est utilise
		{
			count = 0;
		}
		else 
		{
			count += nav->size + 4;
			if(count >= size)
			{
				insert(start, count, size); 
				return (void *) start + 4;
			}
		}
		nav += nav->size / 4 + 1;
	}
	return NULL;
}

void free(void * ptr)
{
	ptr -= 4;
	((header *) ptr)->alloc = 0;
}

int main(int argc, const char *argv[])
{
	myalloc(8);
	int *first = (int *)myalloc(sizeof(int));
	int *second = (int *)myalloc(sizeof(int));
	*first = 1;
	printf("Le premier est %p valeur -> %d \n", first,*first);

	if(second == NULL)
		printf("It's work \n");
	free(first);
	second = (int *)myalloc(sizeof(int));
	*second = 2;
	printf("Le premier est %p valeur -> %d \n", first,*first);
	printf("Le deuxieme est %p valeur -> %d \n", second, *second);
}
