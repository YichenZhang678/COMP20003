#ifndef _DRIVER_H_
#define _DRIVER_H_
#include <stdio.h>
#include "list.h"
#include "dict.h"
#include "data.h"

//function definitions
void stage1(FILE* in_file,FILE* out_file);
list_t* dictBuild(FILE* infile);
void dataPrint(FILE* f, data_t* data);
void querySearch(FILE* f, char* query, list_t* dict);
void listFree(list_t *list, void (*dataFree)(data_t*));
void dataFree(data_t* data);


#endif
