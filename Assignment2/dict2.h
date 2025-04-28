#ifndef _DICT_H_
#define _DICT_H_
#include <stdio.h>
#include "array.h"
#include "data.h"

//constant definition
#define MAX_LINE_LEN 512

//function definitions
void stage2(FILE* in_file,FILE* out_file);
array_t* dictBuild(FILE* infile);
void dataPrint(FILE* f, data_t* data);
void querySearch(FILE* f, char* query, array_t* dict);


#endif
