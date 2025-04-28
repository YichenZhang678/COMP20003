#ifndef _RADIX_TREE_H_
#define _RADIX_TREE_H_
#include "data.h"
#include "list.h"

// datatype definitions
typedef data_t* info_t;

// struct definitions
typedef struct radix_tree {
	list_t* values;
    char* prefix;
    int prefix_length;
    struct radix_tree* left_child;
    struct radix_tree* right_child;
} radix_tree_t;

//define function
radix_tree_t* make_empty_radix_tree();
radix_tree_t* insert_radix_tree(radix_tree_t* radix_tree, info_t value, int start);
radix_tree_t* tree_search(radix_tree_t* radix_tree, char* trading_name, int start, int* b_counter, int* c_counter);
void radix_treeFree(radix_tree_t* radix_tree, void (*dataFree)(data_t*));
void dataFree(data_t* data);
void radix_tree_traverse(FILE* f, radix_tree_t* radix_tree);


#endif

