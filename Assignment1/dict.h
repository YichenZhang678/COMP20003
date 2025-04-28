#ifndef _DICT_H_
#define _DICT_H_
#include <stdio.h>
#include "list.h"

//constant definition
#define MAX_LINE_LEN 512


//function definitions
list_t* dictBuild(FILE* infile);
void querySearch(FILE* f, char* query, list_t* dict);
void dataPrint(FILE* f, data_t* data);


#endif
