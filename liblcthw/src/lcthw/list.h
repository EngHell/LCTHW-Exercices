/*H**********************************************************************
* FILENAME :        list.h             DESIGN REF: :v
*
* DESCRIPTION :
*       Simple double linked structure
*
* NOTES :
*       This file has part of the lcthw book original and improvements
*
*H*/
#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode;

typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

List *List_create();
// This clear all the nodes but not their values
void List_destroy(List * list);
// This clear all the values from the nodes but not the nodes
void List_clear(List *list);
// The result of both from above but in only one loop.
void List_clear_destroy(List *lis);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

// Extra credit operations
void List_copy(List *from, List *to);
List *List_join(List *first, List *second);
void List_split(List *first, List *second, List *from, int index);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
ListNode *V = NULL;\
for(V = _node = L->S; _node!= NULL; V = _node = _node->M)

#endif