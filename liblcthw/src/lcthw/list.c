#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create() {
	return calloc(1, sizeof(List));
}

// This clear all the nodes but not their values
void List_destroy(List * list){
	check(list, "List can't be null");
	
	LIST_FOREACH(list, first, next, cur){
		if(cur->prev){
			free(cur->prev);
		}
	}
	
	free(list->last);
	free(list);
	
	error:
	return;
}

// This clear all the values from the nodes but not the nodes
void List_clear(List *list) {
	check(list, "List can't be null");
	
	LIST_FOREACH(list, first, next, cur){
		free(cur->value);
	}
	
	error:
	return;
}

void List_clear_destroy(List *list){
	check(list, "List can't be null");
	
	LIST_FOREACH(list, first, next, cur){
		free(cur->value);
		
		if(cur->prev){
			free(cur->prev);
		}
	}
	
	free(list->last);
	free(list);
	
	//List_clear(list);
	//List_destroy(list);
	
	error:
	return;
}

void List_push(List *list, void *value){
	check(list, "List can't be null");
	
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->last == NULL) {
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	
	list->count++;
	
	error:
	return;
}

void *List_pop(List *list){
	check(list, "List can't be null");
	
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
	
	error:
	return NULL;
}

void List_unshift(List * list, void *value){
	check(list, "List can't be null");
	
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->first == NULL){
		list->first = node;
		list->last = node;
	} else {
		node->next =list->first;
		list->first->prev = node;
		list->first = node;
	}
	
	list->count++;
	
	error:
	return;
}

void *List_shift(List * list) {
	check(list, "List can't be null");
	
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
	
	error:
	return NULL;
}

void *List_remove(List *list, ListNode *node){
	void *result = NULL;
	check(list, "List can't be null");
	
	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL");
	
	if(node == list->first && node == list->last){
		list->first = NULL;
		list->last = NULL;
	} else if (node == list->first){
		list->first = node->next;
		check(list->first != NULL,
		"Invalid list, somehow got a first that is NULL.");
		list->first->prev = NULL;
	} else if(node == list->last){
		list->last = node->prev;
		check(list->last != NULL,
		"Invalid list, somehow got a next that is NULL.");
		list->last->next =NULL;
	} else {
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}
	
	list->count--;
	result = node->value;
	free(node);
	
	error:
	return result;
}


// Extra credit operations
void List_copy(List *from, List *to) {
	check(from,"from can't be NULL");
	check(to, "to can't be NULL");
	
	LIST_FOREACH(from, first, next, cur){
		List_push(to, cur->value);
	}
	error: 
	return;
}

List *List_join(List *first, List *second){
	List *list = calloc(1,sizeof(List));
	
	list->first = first->first;
	first->last->next = second->first;
	list->last = second->last;
	list->count = List_count(first) + List_count(second);

	
	return list;
}

void List_split(List *first, List *second, List *from, int index) {
	check(from, "from can't be null on split")
	check(first, "first can't be null on split")
	check(second, "second can't be null on split")
	check(index <= List_count(from), "index can't be higher than the count of elements on from");
	
	/* 
	 * in there, is because for some reason the compiler thinks this var
	 * is part of the for loop auxiliars and then destroy it after the for loop ends
	 */
	ListNode *first_last = from->first;
	
	// 1 because we already retrived the first one above
	
	for(int i = 1; i < index; ++i){
		first_last = first_last->next;
	}
	
	ListNode *second_first = first_last->next;
	second_first->prev = NULL;
	first_last->next =NULL;
	
	first->first = from->first;
	first->last = first_last;
	first->count = index;
	
	second->first = second_first;
	second->last = from->last;
	second->count = List_count(from) - index;
	
	return;
	
	
	error:
	return;
}