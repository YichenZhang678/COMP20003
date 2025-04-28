#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "driver.h"

 
int main(int argc, char *argv[]) {
	// check command line argument = 4
	if (argc != 4) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
		exit(EXIT_FAILURE);
	} 
    //open data file & output file to get FILE pointer
	FILE* inFile = fopen(argv[2], "r");
	if (!inFile) {
    	fprintf(stderr, "Error opening input file: %s\n", argv[2]);
    	return EXIT_FAILURE;
	}
    FILE* outFile = fopen(argv[3], "w");
    if (!outFile) {
        fprintf(stderr, "Error opening output file: %s\n", argv[3]);
        fclose(inFile);
        return 1;
    }
    //check command line argument and run the stage
    if (atoi(argv[1]) == 1) {
        stage1(inFile, outFile);
    } 
    else{
        fprintf(stderr, "Invalid stage specified\n");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }
    fclose(inFile);	
    fclose(outFile);
    return 0;
}

//search and print cafe information and number of chain cafe
void stage1(FILE* in_file, FILE* out_file){
	list_t* dict = dictBuild(in_file);
    char* query = malloc(sizeof(char) * (MAX_CHAR_LEN + 1));
    assert(query);
    while(scanf(" %[^\n]", query) == 1){
        querySearch(out_file, query, dict);
    }
    free(query);
    listFree(dict, (void (*)(data_t*))dataFree);
}
  





