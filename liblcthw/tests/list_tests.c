#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>
#include <stdlib.h>

static List *list = NULL;
static List *list2 = NULL;
char *test1;
char *test2;
char *test3;
char *test4;
char *test5;

char *test_create() {
	list = List_create();
	mu_assert(list != NULL, "Failed to create list.");
	
	list2 = List_create();
	mu_assert(list2 != NULL, "Failed to create list2");
	
	return NULL;
}

char *test_destroy(){
	List_clear_destroy(list);
	
	return NULL;
}

char *test_push_pop() {
	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last value.");
	
	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last value.");
	
	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last value");
	mu_assert(List_count(list) == 3, "Wrong count on push.");
	
	char *val = List_pop(list);
	mu_assert(val == test3, "Wrong value on pop.");
	
	val = List_pop(list);
	mu_assert(val == test2, "Wrong value on pop.");
	
	val = List_pop(list);
	mu_assert(val == test1, "Wrong value on pop.");
	mu_assert(List_count(list) == 0, "Wrong count after pop.");
	
	return NULL;
}

char *test_unshift(){
	List_unshift(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first value.");
	
	List_unshift(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first value");
	
	List_unshift(list, test3);
	mu_assert(List_first(list) == test3, "Worng first value");
	mu_assert(List_count(list) == 3, "Wrong count on unshift.");
	
	return NULL;
}

char *test_remove() {
	// we only need to test the middle remove cas since push/shift
	// already test the other cases
	char *val = List_remove(list, list->first->next);
	mu_assert(val == test2, "Wrong removed element.");
	mu_assert(List_count(list) == 2, "Wrong count after remove.");
	mu_assert(List_first(list) == test3, "Wrong first after remove.");
	mu_assert(List_last(list) == test1, "Wrong last after remove.");
	
	return NULL;
}

char *test_shift() {
	mu_assert(List_count(list) != 0, "Wrong count before sihft.");
	
	char *val = List_shift(list);
	mu_assert(val == test3, "Wrong value on shift.");
	
	val = List_shift(list);
	mu_assert(val == test1, "Wrong value on shift.");
	mu_assert(List_count(list) == 0, "Wrong count after shift.");
	
	return NULL;
}

char *test_copy() {
	List *to = List_create();
	List_copy(list, to);
	
	mu_assert(list->first->value == to->first->value, "First is not the same");
	mu_assert(list->first->next->value == to->first->next->value, "Middle is not the same");
	mu_assert(list->last->value == to->last->value, "First is not the same");
	
	List_destroy(to);
	
	return NULL;
}

char *test_join() {
	List *joint = List_join(list, list2);
	mu_assert(joint != NULL, "Failed to allocate memory for join't");
	
	mu_assert(joint->first == list->first, "Joint first is not the expected first");
	mu_assert(joint->last == list2->last, "Joint last is not the expected last");
	
	free(joint);
	
	return NULL;
}

char *test_operations_on_null() {
	List_destroy(NULL);
	List_clear(NULL);
	List_clear_destroy(NULL);
	List_push(NULL, NULL);
	mu_assert(List_pop(NULL) == NULL, "pop over NULL list not returning NULL");
	List_unshift(NULL, NULL);
	mu_assert(List_shift(NULL) == NULL, "shift over NULL list not returning null");
	mu_assert(List_remove(NULL,NULL) == NULL, "remove over NULL list not returning null");
	
	
	return NULL;
}

void clean_on_fail(){
	if(test1) free(test1);
	if(test2) free(test2);
	if(test3) free(test3);
	if(test4) free(test4);
	if(test5) free(test5);
}

char *all_tests() {
	test1 = calloc(1,sizeof(char));
	test2 = calloc(1,sizeof(char));
	test3 = calloc(1,sizeof(char));
	test4 = calloc(1,sizeof(char));
	test5 = calloc(1,sizeof(char));
	
	
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_copy);
	mu_run_test(test_join);
	mu_run_test(test_shift);
	mu_run_test(test_destroy);
	mu_run_test(test_operations_on_null);
	
	clean_on_fail();
	
	return NULL;
}

RUN_TESTS(all_tests, clean_on_fail);