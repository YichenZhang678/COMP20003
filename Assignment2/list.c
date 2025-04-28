// these code are copied from assignment1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

// function implementation
// make a empty list
// similar to the knowledge learnt in foa
list_t* make_empty_list(void) {
    list_t* list;
    //give a memory size to the list
    list = (list_t*)malloc(sizeof(list_t));
    assert(list);
    
    //for empty list, head node should be NULL, either as foot node
    list->head = NULL;
    list->foot = NULL;

    return list;
}

list_t* insert_at_foot(list_t* list, info_t value) {
    // store value in the node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node && list);

    new_node->info = value;
    new_node->next = NULL;

    // if list is empty
    if (list->head == NULL) {
        // make head node to be the new node
        list->head = new_node;
    } else {
        list->foot->next = new_node;
    }
    // update foot pointer
    list->foot = new_node;
    return list;
}

// free the list
// Using function pointer(Workshop3), we only need to free once instead of 2
// By this way, we can make out code work more efficiently 
void listFree(list_t* list, void (*dataFree)(data_t*)) {
    assert(list != NULL);
    node_t* curr = list->head;
    // use while loop to free the whold lsit
    while (curr) {
        // use pointer to record current node
        node_t* tmp = curr;
        // move current to next node
        curr = curr->next;
        dataFree(tmp->info);
        // free the node
        free(tmp);
    }
    // free the list
    free(list);
}
