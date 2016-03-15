#include <stdlib.h> 
#include <stdio.h>
#include <CUnit/Basic.h>
#include "Mymalloc.h"

int init(void) {
	void *ptr = mymalloc(20);
	if(ptr != NULL) //Initialisation du heap d'une taille de 16 bytes
		return 0;
	return 1;
}

void ajout(void) {
	int *ptr=(int *)mymalloc(sizeof(int));
	*ptr = 42;
	CU_ASSERT_EQUAL(*ptr, 42);
	myfree(ptr);
}

void full(void) {
	void *first = mymalloc(sizeof(long));
	int *ptr = (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NULL(mymalloc(sizeof(int)));
	myfree(first);
	myfree(ptr);
}

void freetest(void) {
	void *first = mymalloc(sizeof(long));
	int *ptr = (int *)mymalloc(sizeof(int));
	myfree(first);
	void *second = mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(second);
	myfree(ptr);
	myfree(second);
}

void callocTest(void) {
	int *first = (int *)mymalloc(sizeof(int));
	int *second= (int *)mymalloc(sizeof(int));
	*first = 42;
	myfree(first);
	int *third = (int *)mycalloc(sizeof(int));
	CU_ASSERT_EQUAL(*third, 0);
	myfree(second);
	myfree(third);
}

void avFrag(void) {
	long *first = (long *)mymalloc(sizeof(long));
	int *deux = (int *)mymalloc(sizeof(int));
	myfree(first);
	int *trois = (int*)mymalloc(sizeof(int));
	myfree(deux);
	long* quattre = (long *)mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(quattre);
	myfree(quattre);
	myfree(trois);
}

void frag(void) {
	void *un = mymalloc(sizeof(int));
	void *deux = mymalloc(sizeof(int));
	myfree(un);
	myfree(deux);
	void *quattre = mymalloc(12);
	CU_ASSERT_PTR_NOT_NULL(quattre);
	myfree(quattre);
}

int main(int argc, const char *argv[]) {

	CU_pSuite pSuite = NULL;
	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite",init,NULL);
	if(NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add the tests to the suite */
	/* NOTE - ORDER IS IMPORTANT - first fct added = first to be run */
	if((NULL == CU_add_test(pSuite, "Malloc", ajout)) ||
			(NULL == CU_add_test(pSuite, "NULL", full)) ||
			(NULL == CU_add_test(pSuite, "free", freetest)) ||
			(NULL == CU_add_test(pSuite, "Fragementation", frag)) ||
			(NULL == CU_add_test(pSuite, "Fragmentation avance", avFrag)) ||
			(NULL == CU_add_test(pSuite, "Calloc", callocTest))
			) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
