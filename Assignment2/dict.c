// code copied from assignment 1
#include "dict.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int main(int argc, char* argv[]) {
    // check command line argument = 4
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // open data file & output file to get FILE pointer
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
    // check command line argument and run the stage
    if (atoi(argv[1]) == 1) {
        stage1(inFile, outFile);
    } else {
        fprintf(stderr, "Invalid stage specified\n");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }
    fclose(inFile);
    fclose(outFile);
    return 0;
}

// search and print cafe information and number of chain cafe
void stage1(FILE* in_file, FILE* out_file) {
    list_t* dict = dictBuild(in_file);
    char* query = malloc(sizeof(char) * (MAX_CHAR_LEN + 1));
    assert(query);
    while (scanf(" %[^\n]", query) == 1) {
        querySearch(out_file, query, dict);
    }
    free(query);
    listFree(dict, (void (*)(data_t*))dataFree);
}

// Use linkedlist method to build a dictionary
// And read the data from input file and then record it
list_t* dictBuild(FILE* infile) {
    // store struct pointer into node in linked list
    list_t* dict = make_empty_list();
    char* buffer = malloc(sizeof(char) * (MAX_LINE_LEN + 1));
    assert(buffer);
    // skip the frist line
    dataSkipHeaderLine(infile);
    while (fgets(buffer, MAX_LINE_LEN + 1, infile) != NULL) {
        // every line text will be a struct
        data_t* data = dataRead(buffer);
        // append data struct in list
        dict = insert_at_foot(dict, data);
    }
    // free the buffer
    free(buffer);
    return dict;
}

// Find the information of the input from stdin
// And count the number
void querySearch(FILE* f, char* query, list_t* dict) {
    node_t* curr = dict->head;
    int count = 0;
    while (curr) {
        if (strcmp(query, curr->info->trading_name) == 0) {
            count++;
            if (count == 1) {  // ensure one trading_name print once
                fprintf(f, "%s\n", query);
            }
            dataPrint(f, curr->info);
        }
        curr = curr->next;
    }
    if (count == 0) {
        fprintf(stdout, "%s --> NOT FOUND\n", query);

    }  // print number of chain cafe
    else {
        fprintf(stdout, "%s --> %d\n", query, count);
    }
}
