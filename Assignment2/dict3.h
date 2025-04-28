#ifndef _DICT_H_
#define _DICT_H_
#include <stdio.h>
#include "radix_tree.h"
#include "data.h"

//constant definition
#define MAX_LINE_LEN 512

//function definitions
void stage3(FILE* in_file,FILE* out_file);
radix_tree_t* dictBuild(FILE* infile);
void dataPrint(FILE* f, data_t* data);
void querySearch(FILE* f, char* query, radix_tree_t* dict);


#endif
