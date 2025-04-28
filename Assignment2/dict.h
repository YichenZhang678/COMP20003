//code copied from assignment 1
#ifndef _DICT_H_
#define _DICT_H_
#include <stdio.h>
#include "list.h"
#include "data.h"

//constant definition
#define MAX_LINE_LEN 512

//function definitions
void stage1(FILE* in_file,FILE* out_file);
list_t* dictBuild(FILE* infile);
void dataPrint(FILE* f, data_t* data);
void querySearch(FILE* f, char* query, list_t* dict);
void listFree(list_t *list, void (*dataFree)(data_t*));
void dataFree(data_t* data);


#endif
