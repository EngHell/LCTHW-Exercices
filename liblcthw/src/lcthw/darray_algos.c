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

static inline void swap(void ** a, void ** b) {
	/*char * temp = calloc(1, size);

	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b,temp, size);

	free(temp);*/

	void * temp = NULL;
	temp = *a;
	*a = *b;
	*b = temp;


}

static inline int index(int pos, int size) {
	return pos * size;
}

int My_qsort(void * base, int count, size_t size, DArray_compare cmp) {
	if(count <= 1)
		return 0;

	void ** data= base;

	int pivot_index = 0; //rand() % count;
	int max_left = 0;
	int right_index = 0;

	void *start = data[0];
	void *pivot = data[pivot_index];

	swap(&data[0], &data[pivot_index]);

	for(int i = 1; i < count; i++){
		if(cmp(&pivot, &data[i]) > 0){
			max_left++;

			swap(&data[i], &data[max_left]);
		}
	}

	swap(&data[0], &data[max_left]);

	My_qsort(data, max_left, size, cmp);

	My_qsort(data + max_left + 1, count - max_left -1, size, cmp);

	return 0;
}

int MDArray_qsort(DArray * array, DArray_compare cmp) {

	return My_qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}