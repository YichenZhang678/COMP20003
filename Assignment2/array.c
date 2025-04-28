#include "array.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// function implementation
// make a empty array
array_t* make_empty_array() {
    array_t* array;
    // give a memory size to the array
    array = (array_t*)malloc(sizeof(array_t));
    assert(array);

    // for empty array, size should be 0, capacity should be 20
    array->info_size = 0;
    array->info_capacity = 20;

    // give a memory size to the array
    array->values = (info_t*)malloc(array->info_capacity * sizeof(info_t));
    assert(array->values);

    return array;
}

// insert a value into the array in the ascending order
array_t* insert_ordered(array_t* array, info_t value) {
    // if array is full, double the size
    if (array->info_size == array->info_capacity) {
        array->info_capacity * 2;
        array->values = (info_t*)realloc(array->values,
                                         array->info_capacity * sizeof(info_t));
        assert(array->values);
    }
    // if array is empty
    if (array->info_size == 0) {
        array->values[0] = value;
        array->info_size++;
        return array;
    }
    // if array is not empty
    int i = array->info_size;
    // find the position to insert
    while (i >= 1) {
        if (strcmp(value->trading_name, array->values[i - 1]->trading_name) >=
            0) {
            array->values[i] = value;
            array->info_size++;
            return array;
        } else {
            array->values[i] = array->values[i - 1];
            i--;
        }
    }
    array->values[0] = value;
    array->info_size++;
    return array;
}

// binary search the trading_name in the array, in the range of start to end
int binary_search(array_t* array,
                  char* trading_name,
                  int start,
                  int end,
                  int* c_counter,
                  int* s_counter) {
    if (start <= end) {
        int current = (start + end) / 2;
        int result =
            string_compare(trading_name, array->values[current]->trading_name,
                           c_counter, s_counter);
        if (result < 0) {
            return binary_search(array, trading_name, start, current - 1,
                                 c_counter, s_counter);
        } else if (result > 0) {
            return binary_search(array, trading_name, current + 1, end,
                                 c_counter, s_counter);
        } else {
            return current;
        }
    } else {
        return -1;
    }
}

// linear search the trading_name in the array, from start to end
int linear_search(array_t* array,
                  char* trading_name,
                  int start,
                  int end,
                  int* c_counter,
                  int* s_counter) {
    if (start > end) {
        for (int current = start; current >= end; current--) {
            int result = string_compare(trading_name,
                                        array->values[current]->trading_name,
                                        c_counter, s_counter);
            if (result != 0) {
                return current;
            }
        }
    } else {
        for (int current = start; current <= end; current++) {
            int result = string_compare(trading_name,
                                        array->values[current]->trading_name,
                                        c_counter, s_counter);
            if (result != 0) {
                return current;
            }
        }
    }
    if (start > end) {
        return end - 1;
    } else {
        return end + 1;
    }
}

// free the array
void arrayFree(array_t* array, void (*dataFree)(data_t*)) {
    for (int i = 0; i < array->info_size; i++) {
        dataFree(array->values[i]);
    }
    free(array->values);
    free(array);
}

// when str1 is the prefix of str2, return 0
// when str1 < str2, return -1
// when str1 > str2, return 1
int string_compare(char* str1, char* str2, int* c_counter, int* s_counter) {
    (*s_counter)++;
    while (*str1 != '\0' && *str2 != '\0') {
        (*c_counter)++;
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        str1++;
        str2++;
    }
    (*c_counter)++;
    if (*str1 == '\0') {
        // str1 is the prefix of str2
        return 0;
    } else {
        return 1;
    }
}
