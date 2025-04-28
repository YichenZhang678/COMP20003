#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>

// Constant definitions
#define MAX_CHAR_LEN 128
#define MAX_LINE_LEN 512
#define SECTIONS_NUMBER 14

//struct for cafe information
typedef struct {
    int census_year, block_id, property_id, base_property_id;
    char* building_address;
	char* clue_small_area;
	char* business_address;
	char* trading_name;
    int industry_code;
    char* industry_description;
	char* seating_type;
    int number_of_seats;
    double longitude, latitude;
} data_t;

//define functions
void dataSkipHeaderLine(FILE *f);
data_t* dataRead(char* line);
void dataPrint(FILE* f, data_t* data);
void dataFree(data_t* data);
  
#endif
