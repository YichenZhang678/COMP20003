#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dict.h"
#include "data.h"


// Use linkedlist method to build a dictionary
// And read the data from input file and then record it
list_t* dictBuild(FILE* infile){
	//store struct pointer into node in linked list
    list_t* dict=make_empty_list(); 
	char* buffer = malloc(sizeof(char)*(MAX_LINE_LEN + 1)); 
	assert(buffer);
	//skip the frist line 
	dataSkipHeaderLine(infile);
	while(fgets(buffer, MAX_LINE_LEN + 1,infile)!= NULL){
		//every line text will be a struct
		data_t* data = dataRead(buffer);
		//append data struct in list
		dict = insert_at_foot(dict, data); 
	}
	//free the buffer
	free(buffer);
	return dict;
}

// Find the information of the input from stdin
// And count the number
void querySearch(FILE* f, char* query, list_t* dict){
	node_t* curr = dict->head;
	int count = 0;
	while(curr){
		if(strcmp(query,curr->info->trading_name) == 0){
			count++;
			if(count==1){ //ensure one trading_name print once
				fprintf(f,"%s\n",query);}
			dataPrint(f,curr->info);
		}
		curr = curr->next;
	}
	if(count == 0){
		fprintf(stdout,"%s --> NOT FOUND\n",query);

	}//print number of chain cafe
	else{fprintf(stdout,"%s --> %d\n",query,count);
}
}




