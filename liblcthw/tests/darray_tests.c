//
// Created by dev1 on 8/01/18.
//
#include <lcthw/darray.h>
#include "minunit.h"
#include <stdio.h>

static DArray * array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

DArray *create_array(){
	return DArray_create(sizeof(int), 100);
}

char *test_create(){
	array = create_array();
	mu_assert(array != NULL, "DArray_create failed.");
	mu_assert(array->contents != NULL, "contents are wrong in darray");
	mu_assert(array->end == 0, "end isn't at the right spot");
	mu_assert(array->element_size == sizeof(int),
	"element size is wrong.");
	mu_assert(array->max == 100, "Wrong max length on initial size");

	return  NULL;
}



char *test_new() {

	val1 = DArray_new(array);
	mu_assert(val1 != NULL, "failed to make a new element");

	val2 = DArray_new(array);
	mu_assert(val2 != NULL, "failed to make a new element");

	return NULL;

}

char *test_set_and_get() {
	DArray_set(array, 0, val1);
	DArray_set(array, 1, val2);

	mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
	mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");

	return NULL;
}

char *test_remove() {
	int *val_check = DArray_remove(array, 0);
	mu_assert(val_check != NULL, "Should not get NULL");
	mu_assert(*val_check == *val1, "Should get the first value.");
	mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
	DArray_free(val_check);

	val_check = DArray_remove(array, 1);
	mu_assert(val_check != NULL, "Should not get NULL");
	mu_assert(*val_check == *val2, "Should get the second value.");
	mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
	DArray_free(val_check);

	return NULL;
}

char *test_expand_contract() {
	size_t old_max = array->max;
	DArray_expand(array);
	mu_assert(array->max == old_max + array->expand_rate, "Wrong size after expand.");

	DArray_contract(array);
	mu_assert(array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");

	return NULL;

}

char *test_push_pop() {
	int i = 0;
	for(i = 0; i < 1000; i++){
		int *val = DArray_new(array);
		*val = i * 333;
		DArray_push(array, val);
	}

	mu_assert(array->max == 1201, "Wrong max size.");

	for(i = 999; i>=0; i--){
		int *val = DArray_pop(array);
		mu_assert(val != NULL, "Shouldn't get a NULL.");
		mu_assert(*val == i * 333, "Wrong value.");
		DArray_free(val);
	}

	return NULL;
}

char *test_destroy(){
	DArray_destroy(&array);

	return NULL;
}

char *test_clear_and_destroy() {
	array = DArray_create(sizeof(int *), 100);
	for(int i = 0; i < 500; i++){
		int *val = DArray_new(array);
		*val = i;
		DArray_push(array, val);
	}

	DArray_clear_destroy(&array);

	mu_assert(array == NULL, "Should be null");

	return NULL;
}

static inline void swap(void * a, void * b, size_t size) {
	char * temp = calloc(1, size);

	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b,temp, size);

	free(temp);

}

void func(int ** i){
	*i = malloc(sizeof(int));
}

char *some_test() {
	array = DArray_create(sizeof(int *), 10);
	int * val = DArray_new(array);
	*val = 1;
	DArray_set(array, 0, val);

	printf("whatever is there: %d\n", *(int *)DArray_get(array, 0));

	*val = 2;

	printf("now it's: %d\n", *(int *)DArray_get(array, 0));

	int *val2 = malloc( sizeof(int) );
	*val2 = 5;

	swap(val, val2, sizeof(int));

	printf("after sawp val is: %d\n", *val);
	printf("after sawp val2 is:%d\n", *val2);


	DArray_clear_destroy(&array);

	int * hi = NULL;
	func(&hi);

	printf("Pointer value: %p\n", hi);

	if(hi)
		free(hi);

	return NULL;
}



char *all_tests() {
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set_and_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract)
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);

	mu_run_test(some_test);

	mu_run_test(test_clear_and_destroy);

	return NULL;
}

void clean() {
	if(val1)
		free(val1);

	if(val2)
		free(val2);
}

RUN_TESTS(all_tests, clean);

