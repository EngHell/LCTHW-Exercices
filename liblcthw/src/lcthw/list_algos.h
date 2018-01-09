//
// Created by dev1 on 3/12/17.
//

#ifndef LCTHW_LIST_ALGOS_H
#define LCTHW_LIST_ALGOS_H

#include <lcthw/list.h>

typedef int (*List_compare)(const void *cur, const void *next);
int List_bubble_sort(List * list, List_compare cmp);
int List_merge_sort(List * list, List_compare cmp);

#endif //LCTHW_LIST_ALGOS_H
