#ifndef _LIST_H_
#define _LIST_H_
#include "data.h"

// datatype definitions
typedef data_t* info_t;

typedef struct node node_t;

//struct of information
struct node {
    info_t info;
    node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

//define function
list_t *make_empty_list();
list_t *insert_at_foot(list_t *list, info_t value);
void listFree(list_t *list, void (*dataFree)(data_t*));
void dataFree(data_t* data);


#endif

