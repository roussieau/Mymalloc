#include <stdlib.h> 
#include <stdio.h>
#include <CUnit/Basic.h>
#include "Mymalloc.h"

void ajout(void) {
	int *ptr=(int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(ptr);
	*ptr = 42;
	CU_ASSERT_EQUAL(*ptr, 42);
	myfree(ptr);
}

void full(void) {
	void *first = mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(first);
	int *ptr = (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(ptr);
	CU_ASSERT_PTR_NULL(mymalloc(sizeof(int)));
	myfree(first);
	myfree(ptr);
}

void freetest(void) {
	void *first = mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(first);
	int *ptr = (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(ptr);
	myfree(first);
	void *second = mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(second);
	myfree(ptr);
	myfree(second);
}

void callocTest(void) {
	int *first = (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(first);
	int *second= (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(second);
	*first = 42;
	myfree(first);
	int *third = (int *)mycalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(third);
	CU_ASSERT_EQUAL(*third, 0);
	myfree(second);
	myfree(third);
}

void avFrag(void) {
	long *first = (long *)mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(first);
	int *deux = (int *)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(deux);
	myfree(first);
	int *trois = (int*)mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(trois);
	myfree(deux);
	long* quattre = (long *)mymalloc(sizeof(long));
	CU_ASSERT_PTR_NOT_NULL(quattre);
	myfree(quattre);
	myfree(trois);
}

void frag(void) {
	void *un = mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(un);
	void *deux = mymalloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL(deux);
	myfree(un);
	myfree(deux);
	void *quattre = mymalloc(12);
	CU_ASSERT_PTR_NOT_NULL(quattre);
	myfree(quattre);
}

int main(int argc, const char *argv[]) {
	if(argc == 2)
		mymalloc(atoi(argv[1]));
	else
		mymalloc(20);
	CU_pSuite pSuite = NULL;

	/* initialisation de la suite*/
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* création de la suite */
	pSuite = CU_add_suite("Suite",NULL,NULL);
	if(NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Ajout à la suite */
	if(NULL == CU_add_test(pSuite, "Malloc", ajout) ||
	   NULL == CU_add_test(pSuite, "NULL", full) ||
	   NULL == CU_add_test(pSuite, "free", freetest) ||
	   NULL == CU_add_test(pSuite, "Fragementation", frag) ||
       NULL == CU_add_test(pSuite, "Fragmentation avance", avFrag) ||
	   NULL == CU_add_test(pSuite, "Calloc", callocTest)
			) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Lancement des tests */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
