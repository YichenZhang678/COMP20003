#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"

// datatype definitions
typedef data_t* info_t;

// struct definitions
typedef struct {
	info_t* values;
    int info_size;
    int info_capacity;
} array_t;

//define function
array_t* make_empty_array();
array_t* insert_ordered(array_t* array, info_t value);
int binary_search(array_t* array, char* trading_name, int start, int end, int* c_counter, int* s_counter);
int linear_search(array_t* array, char* trading_name, int start, int end, int* c_counter, int* s_counter);
void arrayFree(array_t* array, void (*dataFree)(data_t*));
void dataFree(data_t* data);
int string_compare(char* str1, char* str2, int* c_counter, int* s_counter);


#endif

