#include <lcthw/darray_algos.h>
#include <bsd/stdlib.h>

int DArray_qsort(DArray * array, DArray_compare cmp){
	qsort(array->contents, (int)DArray_count(array), sizeof(void *), cmp);
	return 0;
}

int DArray_heapsort(DArray * array, DArray_compare cmp){
	return heapsort(array->contents, (int)DArray_count(array), sizeof(void*), cmp);
}

int DArray_mergesort(DArray * array, DArray_compare cmp) {
	return mergesort(array->contents, (int)DArray_count(array),
	sizeof(void *), cmp);

}