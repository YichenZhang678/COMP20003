#include "radix_tree.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// make a empty radix_tree
radix_tree_t* make_empty_radix_tree() {
    return NULL;
}

// insert a value into the radix_tree
radix_tree_t* insert_radix_tree(radix_tree_t* radix_tree, info_t value, int start) {
    if (radix_tree == NULL) {
        // give a memory size to the radix_tree
        radix_tree = (radix_tree_t*)malloc(sizeof(radix_tree_t));
        assert(radix_tree);

        // initialize the list
        radix_tree->values = make_empty_list();
        radix_tree->values = insert_at_foot(radix_tree->values, value);

        // initialize the children
        radix_tree->left_child = NULL;
        radix_tree->right_child = NULL;

        // initialize the prefix
        radix_tree->prefix = strdup(value->trading_name);
        radix_tree->prefix_length = (strlen(value->trading_name) + 1) << 3;
        assert(radix_tree->prefix);

        return radix_tree;
    }

    int current_start = start & 0b111;
    int index_bit = 0;
    int current_bit = current_start + index_bit;
    int value_bit = start + index_bit;
    int tree_end_bit = radix_tree->prefix_length;
    int value_end_bit = (strlen(value->trading_name) + 1) << 3;
    while (index_bit < tree_end_bit && value_bit < value_end_bit) {
        // get the bit of the current radix_tree and the value
        int char1_index = current_bit >> 3;
        int char2_index = value_bit >> 3;
        int char1_bit = current_bit & 0b111;
        int char2_bit = value_bit & 0b111;
        int char1 = radix_tree->prefix[char1_index];
        int char2 = value->trading_name[char2_index];
        int bit1 = (char1 >> (7 - char1_bit)) & 1;
        int bit2 = (char2 >> (7 - char2_bit)) & 1;
        
        if (bit1 != bit2) {
            // split the current radix_tree
            // tree1 use the same data as current radix_tree
            radix_tree_t* radix_tree1 = (radix_tree_t*)malloc(sizeof(radix_tree_t));
            assert(radix_tree1);
            radix_tree1->values = radix_tree->values;
            radix_tree1->prefix = strdup(radix_tree->prefix + (current_bit >> 3));
            assert(radix_tree1->prefix);
            radix_tree1->prefix_length = tree_end_bit - index_bit;
            radix_tree1->left_child = radix_tree->left_child;
            radix_tree1->right_child = radix_tree->right_child;

            // tree2 store the new value
            radix_tree_t* radix_tree2 = (radix_tree_t*)malloc(sizeof(radix_tree_t));
            assert(radix_tree2);
            radix_tree2->values = make_empty_list();
            radix_tree2->values = insert_at_foot(radix_tree2->values, value);
            radix_tree2->prefix = strdup(value->trading_name + (value_bit >> 3));
            assert(radix_tree2->prefix);
            radix_tree2->prefix_length = value_end_bit - value_bit;
            radix_tree2->left_child = NULL;
            radix_tree2->right_child = NULL;
            
            if (bit1 == 1) {
                // update the current radix_tree
                radix_tree->values = make_empty_list();
                radix_tree->prefix_length = index_bit;
                radix_tree->left_child = radix_tree2;
                radix_tree->right_child = radix_tree1;
            } else if (bit1 == 0) {
                // update the current radix_tree
                radix_tree->values = make_empty_list();
                radix_tree->prefix_length = index_bit;
                radix_tree->left_child = radix_tree1;
                radix_tree->right_child = radix_tree2;
            }
            
            return radix_tree;
        } else {
            // update the index
            index_bit++;
            current_bit = current_start + index_bit;
            value_bit = start + index_bit;
        }
    }

    if (index_bit < tree_end_bit && value_bit == value_end_bit) {
        int char1_index = current_bit >> 3;
        int char1_bit = current_bit & 0b111;
        int char1 = radix_tree->prefix[char1_index];
        int bit1 = (char1 >> (7 - char1_bit)) & 1;

        // tree1 use the same data as current radix_tree
        radix_tree_t* radix_tree1 = (radix_tree_t*)malloc(sizeof(radix_tree_t));
        assert(radix_tree1);
        radix_tree1->values = radix_tree->values;
        radix_tree1->prefix = strdup(radix_tree->prefix + (current_bit >> 3));
        assert(radix_tree1->prefix);
        radix_tree1->prefix_length = tree_end_bit - index_bit;
        radix_tree1->left_child = radix_tree->left_child;
        radix_tree1->right_child = radix_tree->right_child;

        // tree2 set to NULL
        radix_tree_t* radix_tree2 = NULL;

        if (bit1 == 1) {
            // update the current radix_tree
            radix_tree->values = make_empty_list();
            insert_at_foot(radix_tree->values, value);
            radix_tree->prefix_length = index_bit;
            radix_tree->left_child = radix_tree2;
            radix_tree->right_child = radix_tree1;
        } else if (bit1 == 0) {
            // update the current radix_tree
            radix_tree->values = make_empty_list();
            insert_at_foot(radix_tree->values, value);
            radix_tree->prefix_length = index_bit;
            radix_tree->left_child = radix_tree1;
            radix_tree->right_child = radix_tree2;
        }
        return radix_tree;
    } else if (index_bit == tree_end_bit && value_bit < value_end_bit) {
        int char2_index = value_bit >> 3;
        int char2_bit = value_bit & 0b111;
        int char2 = value->trading_name[char2_index];
        int bit2 = (char2 >> (7 - char2_bit)) & 1;
        if (bit2 == 1) {
            radix_tree->right_child = insert_radix_tree(radix_tree->right_child, value, value_bit);
            return radix_tree;
        } else {
            radix_tree->left_child = insert_radix_tree(radix_tree->left_child, value, value_bit);
            return radix_tree;
        }
    } else {
        // insert the value into the list
        radix_tree->values = insert_at_foot(radix_tree->values, value);
        return radix_tree;
    }
}

// search the trading_name in the radix_tree
radix_tree_t* tree_search(radix_tree_t* radix_tree, char* trading_name, int start, int* b_counter, int* c_counter) {
    if (radix_tree == NULL) return NULL;    // empty radix tree

    int current_start = start & 0b111;
    int index_bit = 0;
    int current_bit = current_start + index_bit;
    int value_bit = start + index_bit;
    int tree_end_bit = radix_tree->prefix_length;
    int value_end_bit = strlen(trading_name) << 3;
    while (index_bit < tree_end_bit && value_bit < value_end_bit) {
        // get the bit of the current radix_tree and the value
        int char1_index = current_bit >> 3;
        int char2_index = value_bit >> 3;
        int char1_bit = current_bit & 0b111;
        int char2_bit = value_bit & 0b111;
        int char1 = radix_tree->prefix[char1_index];
        int char2 = trading_name[char2_index];
        int bit1 = (char1 >> (7 - char1_bit)) & 1;
        int bit2 = (char2 >> (7 - char2_bit)) & 1;
        (*b_counter)++;
        if ((index_bit & 0b111) == 0) (*c_counter)++;
        
        if (bit1 != bit2) {
            // bit not match
            return NULL;
        } else {
            // update the index
            index_bit++;
            current_bit = current_start + index_bit;
            value_bit = start + index_bit;
        }
    }

    if (index_bit < tree_end_bit && value_bit == value_end_bit) {
        // is the prefix of the radix_tree
        return radix_tree;
    } else if (index_bit == tree_end_bit && value_bit < value_end_bit) {
        int char2_index = value_bit >> 3;
        int char2_bit = value_bit & 0b111;
        int char2 = trading_name[char2_index];
        int bit2 = (char2 >> (7 - char2_bit)) & 1;
        if (bit2 == 1) {
            radix_tree_t* result = tree_search(radix_tree->right_child, trading_name, value_bit, b_counter, c_counter);
            return result;
        } else {
            radix_tree_t* result = tree_search(radix_tree->left_child, trading_name, value_bit, b_counter, c_counter);
            return result;
        }
    } else {
        // all bits match
        return radix_tree;
    }
}

// free the radix_tree
void radix_treeFree(radix_tree_t* radix_tree, void (*dataFree)(data_t*)) {
    if (radix_tree == NULL) return;
    listFree(radix_tree->values, dataFree);
    free(radix_tree->prefix);
    radix_treeFree(radix_tree->left_child, dataFree);
    radix_treeFree(radix_tree->right_child, dataFree);
    free(radix_tree);
}

// traverse the radix_tree
void radix_tree_traverse(FILE* f, radix_tree_t* radix_tree) {
    if (radix_tree == NULL) return;
    list_t* list = radix_tree->values;
    node_t* curr = list->head;
    while (curr) {
        data_t* data = curr->info;
        dataPrint(f, data);
        curr = curr->next;
    }
    radix_tree_traverse(f, radix_tree->left_child);
    radix_tree_traverse(f, radix_tree->right_child);
}
