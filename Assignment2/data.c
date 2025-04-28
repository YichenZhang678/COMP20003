// these code are copied from assignment1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"



// Skip the header line of .csv file "f"(from workshop)
void dataSkipHeaderLine(FILE *f) {
	while (fgetc(f) != '\n');
}

// Reads a data from one line to build a data_t data.
// Returns the pointer
data_t* dataRead(char* line) {
	//initial struct
	data_t* data = malloc(sizeof(data_t));
	assert(data);

	//store 14 sections
	char** sections = malloc(sizeof(char*) * SECTIONS_NUMBER);
	assert(sections);
 
	//store the reading section 
	char* section = malloc(sizeof(char) * (MAX_CHAR_LEN + 1));
	assert(section);

	int indexSections = 0;
	int lenSection = 0;
	int inQuotes = 0;//whether reading comma is in quotes (0:no, 1:yes)

	//extract 14 sections form each row
	char* ptr = line;
	while(*ptr != '\0' && *ptr != '\n' && *ptr != EOF){
		//section end if read a comma
		if(*ptr == ',' && inQuotes == 0){
			section[lenSection] = '\0';
			sections[indexSections] = malloc(sizeof(char)*(lenSection + 1));
			assert(sections[indexSections]);
			strcpy(sections[indexSections],section);
			indexSections++;
			lenSection = 0;
		}
		else if(*ptr == '"'){inQuotes = 1 - inQuotes;}
		else{
			//normal string
			section[lenSection] = *ptr;
			lenSection++;
		}
		ptr++;
	}
	//last section do not have comma
	section[lenSection] = '\0';
	sections[indexSections] = malloc(sizeof(char)*(lenSection + 1));
	assert(sections[indexSections]);
	strcpy(sections[indexSections], section);

	//each section will be stored in struct
	data->census_year = atoi(sections[0]);
	data->block_id = atoi(sections[1]);
	data->property_id = atoi(sections[2]);
	data->base_property_id = atoi(sections[3]);
	data->building_address = strdup(sections[4]);
	data->clue_small_area = strdup(sections[5]);
	data->business_address = strdup(sections[6]);
	data->trading_name = strdup(sections[7]);
	data->industry_code = atoi(sections[8]);
	data->industry_description = strdup(sections[9]);
	data->seating_type = strdup(sections[10]);
	data->number_of_seats = atoi(sections[11]);
	char *endP; 
	data->longitude = strtod(sections[12], &endP);
	data->latitude = strtod(sections[13], &endP);
	//free 14 sections
    free(section);
	for (int i = 0;i < SECTIONS_NUMBER; i++){
		free(sections[i]);
	}
	free(sections);
	return data;
}  


//print data record in outfile
void dataPrint(FILE* f, data_t* data){
    fprintf(f, "--> census_year: %d || ", data->census_year);
	fprintf(f, "block_id: %d || ", data->block_id);
	fprintf(f, "property_id: %d || ", data->property_id);
	fprintf(f, "base_property_id: %d || ", data->base_property_id);
	fprintf(f, "building_address: %s || ", data->building_address);
	fprintf(f, "clue_small_area: %s || ", data->clue_small_area);
	fprintf(f, "business_address: %s || ", data->business_address);
	fprintf(f, "trading_name: %s || ", data->trading_name);
	fprintf(f, "industry_code: %d || ", data->industry_code);
	fprintf(f, "industry_description: %s || ", data->industry_description);
	fprintf(f, "seating_type: %s || ", data->seating_type);
	fprintf(f, "number_of_seats: %d || ", data->number_of_seats);
	fprintf(f, "longitude: %.5lf || ", data->longitude);
	fprintf(f, "latitude: %.5lf || \n", data->latitude);
}

//free the malloc memory in data(char* free)
void dataFree(data_t* data){
	free(data->building_address);
	free(data->clue_small_area);
	free(data->business_address);
	free(data->trading_name);
	free(data->industry_description);
	free(data->seating_type);
	free(data);
}
