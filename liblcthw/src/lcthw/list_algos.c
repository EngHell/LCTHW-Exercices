//
// Created by dev1 on 3/12/17.
//

#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

/*
 * ListNode functions
 */
extern inline void ListNode_swap(ListNode * a, ListNode * b){
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int List_bubble_sort(List * list, List_compare cmp){
	int sorted =1;

	if(List_count(list) <= 1){
		return 0; // already sorted
	}

	do {
		sorted = 1;
		LIST_FOREACH(list, first, next, cur){
			if(cur->next){
				if(cmp(cur->value, cur->next->value) > 0){
					ListNode_swap(cur, cur->next);
					sorted = 0;
				}
			}
		}
	} while (!sorted);

	/*
	ListNode *cur;
	ListNode *swap;
	ListNode *before;
	ListNode *after;
	 */


	return 0;
}

List *Merge(List * left, List * right, List_compare cmp){
	List *result = List_create();

	void *val = NULL;
	while( List_count(left) > 0 || List_count(right) > 0){
		if(List_count(left) > 0 && List_count(right) > 0){
			if(cmp(left->first->value, right->first->value) < 0){
				val = List_shift(left);
			} else {
				val = List_shift(right);
			}

		} else if(List_count(left) > 0) {
			val = List_shift(left);
		} else if(List_count(right) > 0){
			val = List_shift(right);
		}

		List_push(result, val);
	}

	return result;
}

int List_merge_sort(List * list, List_compare cmp){
	int count = List_count(list);

	if(count <= 1)
		return 0;

	int middle = count/2;
	ListNode *head1 = list->first;
	ListNode *tail1 = head1;

	for(int i = 1; i < middle; i++){
		tail1 = tail1->next;
	}

	ListNode *head2 = tail1->next;
	ListNode *tail2 = list->last;

	tail1->next = NULL;
	head2->prev = NULL;

	List * list1 = List_create();
	list1->first = head1;
	list1->last = tail1;
	list1->count = middle;

	List * list2 = List_create();
	list2->first = head2;
	list2->last = tail2;
	list2->count = count-middle;

	int rc = List_merge_sort(list1, cmp);
	check(rc == 0, "Merge sort of list1 failed");

	rc = List_merge_sort(list2, cmp);
	check(rc == 0, "Merge sort of list2 failed");

	List *temp = Merge(list1, list2, cmp);

	// to this point lis1 and list2 have all their nodes destroyed so calling destroy wouln't loop through a lot of nodes
	List_destroy(list1);
	List_destroy(list2);

	list->first = temp->first;
	list->last = temp->last;
	list->count = temp->count;

	free(temp);

	return 0;

	error:
	free(list1);
	free(list2);

	return 1;
}

