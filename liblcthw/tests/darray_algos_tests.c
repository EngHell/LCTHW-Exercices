#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b) {
	return strcmp(*a, *b);
}

DArray *create_words() {
	DArray *result = DArray_create(0, 5);
	char *words[] = {"asdfasfd",
	                 "werwar", "13234", "howas", "oioj"};
	int i = 0;

	for (i = 0; i < 5; i++) {
		DArray_push(result, words[i]);
	}

	return result;
}

DArray *create_numbers() {
	DArray *result = DArray_create(sizeof(int *), 500);

	for (int i = 0; i < 500; i++) {
		int *val =  DArray_new(result);
		*val = rand();
		DArray_push(result, val);
	}

	return result;
}

int is_sorted(DArray *array) {
	int i = 0;

	for (i = 0; i < DArray_count(array) - 1; i++) {
		if (strcmp(DArray_get(array, i), DArray_get(array, i + 1)) > 0) {
			return 0;
		}
	}

	return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name) {
	DArray *words = create_words();
	mu_assert(!is_sorted(words), "Words should start not sorted.");

	debug("--- Testing %s sorting algorithm", name);
	int rc = func(words, (DArray_compare) testcmp);
	mu_assert(rc == 0, "sort failed");
	mu_assert(is_sorted(words), "didn't sort it");

	DArray_clear_destroy(&words);

	return NULL;
}

char *run_my_tests(int (*func)(DArray *, DArray_compare), const char *name){
	printf("Personalized test\n");
	DArray *words = create_numbers();
	mu_assert(!is_sorted(words), "Words should start not sorted.");

	debug("--- Testing %s sorting algorithm", name);
	int rc = func(words, (DArray_compare) testcmp);
	debug("--- Test finished elapsed time: ");
	mu_assert(rc == 0, "sort failed");
	mu_assert(is_sorted(words), "didn't sort it");

	DArray_clear_destroy(&words);

	return NULL;
}

char *test_qsort() {
	return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort() {
	return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort() {
	return run_sort_test(DArray_mergesort, "mergesort");
}

char *test_my_qsort() {
	return run_my_tests(MDArray_qsort, "my qsort");
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_qsort);

	mu_run_test(test_heapsort);
	mu_run_test(test_mergesort);

	mu_run_test(test_my_qsort);

	return NULL;
}

void clean() {

}

RUN_TESTS(all_tests, clean);