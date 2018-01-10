//
// Created by dev1 on 9/01/18.
//

#ifndef LCTHW_DARRAY_ALGOS_H
#define LCTHW_DARRAY_ALGOS_H

#include <lcthw/darray.h>

typedef int (*DArray_compare) (const void *a, const void *b);
int DArray_qsort(DArray * array, DArray_compare cmp);
int DArray_heapsort(DArray * array, DArray_compare cmp);
int DArray_mergesort(DArray * array, DArray_compare cmp);

// my own implementation :p
int MDArray_qsort(DArray * array, DArray_compare cmp) ;

#endif //LCTHW_DARRAY_ALGOS_H
