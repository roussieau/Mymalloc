/*********************************
 *                               *
 *   My_alloc.c                  *
 *   Implementation de Malloc,   * 
 *   Free et Calloc              *
 *   Author : Julian Roussieau   *
 *            Damien Vaneberck   *
 *                               *
 * *******************************/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

typedef struct block_header {
	unsigned int size : 29;
	unsigned int zero : 2;
	unsigned int alloc : 1; // 1 = alloué et 0 = libre
} header;
 
header *first = NULL; 
size_t *end_heap = NULL;

// Aligne la taille sur 32 bits
static size_t calcul(size_t len) {
	return len % 4 == 0 ? len : len + 4 - (len % 4);
}

// Declare le header du nouveau block depuis la position du pointeur start.
// Si la taille demandée est plus petite que la taille possible, il va créer deux blocks,
// celui qu'on veut et un un block avec l'espace qui reste.
static void insert(header *start, int count, size_t size) {
	start->size = size;
	start->zero = 0;
	start->alloc = 1;

	if((size_t)count == size+4)
		return;

	//Si on a trop de place
	size_t reste = (size_t) count - size - 8;
	start += size/4 + 1;
	start->size = reste;
	start->zero = 0;
	start->alloc = 0;
}

// Alloue un block de taille "size" dans le heap et renvoi son adresse
// Si le heap est trop petit, la methode renvoi NULL.
void *myalloc(size_t size) {
	size = calcul(size); // On verifie qu'on est bien sur un multiple de 32 bits
	if(first == NULL) { //Lors du premier appel, on initialise le heap 
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
	while((size_t *)nav < end_heap) {
		if(count == 0)
			start = nav;

		if(nav->alloc == 1)
			count = 0;

		else {
			count += nav->size + 4;
			if(count >= size) {
				insert(start, count, size); 
				return (void *) start + 4;
			}
		}
		nav += nav->size / 4 + 1; // On déplace nav sur le header suivant 
	} 
	return NULL;// Echec de l'allocation
}

// Libère la zone pointée
void free(void *ptr) {
	ptr -= 4;
	((header *) ptr)->alloc = 0;
}
