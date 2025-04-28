#include "dict2.h"
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
    if (atoi(argv[1]) == 2) {
        stage2(inFile, outFile);
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
void stage2(FILE* in_file, FILE* out_file) {
    array_t* dict = dictBuild(in_file);
    char* query = malloc(sizeof(char) * (MAX_CHAR_LEN + 1));
    assert(query);
    while (scanf(" %[^\n]", query) == 1) {
        querySearch(out_file, query, dict);
    }
    free(query);
    arrayFree(dict, (void (*)(data_t*))dataFree);
}

// Use linkedlist method to build a dictionary
// And read the data from input file and then record it
array_t* dictBuild(FILE* infile) {
    // store struct pointer into node in linked list
    array_t* dict = make_empty_array();
    char* buffer = malloc(sizeof(char) * (MAX_LINE_LEN + 1));
    assert(buffer);
    // skip the frist line
    dataSkipHeaderLine(infile);
    while (fgets(buffer, MAX_LINE_LEN + 1, infile) != NULL) {
        // every line text will be a struct
        data_t* data = dataRead(buffer);
        // append data struct in list
        dict = insert_ordered(dict, data);
    }
    // free the buffer
    free(buffer);
    return dict;
}

// Find the information of the input from stdin
// And count the number
void querySearch(FILE* f, char* query, array_t* dict) {
    int c_counter = 0;
    int s_counter = 0;
    int ret = binary_search(dict, query, 0, dict->info_size - 1, &c_counter,
                            &s_counter);
    if (ret == -1) {
        fprintf(stdout, "%s --> b%d c%d s%d\n", query, c_counter * 8, c_counter,
                s_counter);
    } else {
        int ret1, ret2;
        if (ret + 1 <= dict->info_size - 1) {
            ret1 = linear_search(dict, query, ret + 1, dict->info_size - 1,
                                 &c_counter, &s_counter);
        } else {
            ret1 = ret + 1;
        }
        if (ret - 1 >= 0) {
            ret2 =
                linear_search(dict, query, ret - 1, 0, &c_counter, &s_counter);
        } else {
            ret2 = ret - 1;
        }
        fprintf(f, "%s\n", query);
        for (int i = ret2 + 1; i < ret1; i++) {
            dataPrint(f, dict->values[i]);
        }
        fprintf(stdout, "%s --> b%d c%d s%d\n", query, c_counter << 3,
                c_counter, s_counter);
    }
}
