//
// Created by dev1 on 3/12/17.
//
#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

//char *values[] = {"b", "c", "a", "f", "d" };
char *values[] = {"c", "b", "a"};

const int NUM_VALUES = 3;

List *create_words() {
	int i = 0;
	List *words = List_create();

	for(i = 0; i < NUM_VALUES; i++){
		List_push(words, values[i]);
	}

	return words;
}

int is_sorted(List * words) {
	LIST_FOREACH(words, first, next, cur){
		if(cur->next && strcmp(cur->value, cur->next->value) > 0){
			debug("%s %s", (char *)cur->value, (char *)cur->next->value);
			return 0;
		}
	}

	return 1;
}

char *test_bubble_sort() {
	List *words = create_words();

	// should work on a  list that needs sorting
	int rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort");

	// should work on an already sorted list
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

	List_destroy(words);

	return NULL;
}

char *test_merge_sort() {
	List *words = create_words();
	int rc = List_merge_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Merge sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after merge sort");

	// should work on an already sorted list
	rc = List_merge_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Merge sort of already sorted failed.");
	mu_assert(is_sorted(words), "Words should be sort if already merge sorted.");

	List_destroy(words);

	return  NULL;
}

void clean() {

}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_bubble_sort);
	mu_run_test(test_merge_sort);

	return NULL;
}

RUN_TESTS(all_tests, clean);