#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
   FITNESS_DATA record[100];

   char line[buffer_size];
   char filename[buffer_size];

    // get filename from the user
    printf("Please enter the name of the data file: ");

    // these lines read in a line from the stdin (where the user types)
    // and then takes the actual string out of it
    // this removes any spaces or newlines.
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);

    char choice;
    int counter = 0;

    FILE *input = fopen(filename, "r");
        if (!input)
        {
            printf("Error: File could not be opened\n");
            return 1;
        }
        int buffer = 100;//this part was also taken from read_from_file.c done in lab session and also available on minerva.
        char  line_buffer[buffer];
        while (fgets( line_buffer, buffer, input) != NULL) {
                            
            char date[11];//this variable declaring idea code was taken from strsplit.c 
            char time[6]; 
            char steps[10];
            tokeniseRecord( line_buffer, ",", date, time, steps);//this statement is taken from functions-ex.c available on minerva.
            strncpy(record[counter].date, date, sizeof(record[counter].date));//code idea taken from multiple_records.c on minerva.
            strncpy(record[counter].time, time, sizeof(record[counter].time));
            record[counter].steps = atoi(steps);//statement taken from strsplit.c on minerva which was also done in lab session.

            counter++;

                        
    }
    // Always close your file or c will chew your face off.
    fclose(input);
                    
    printf("Number of records in file: %i\n", counter);

    for (int i = 0; i < counter; i++) {//here I am using i<3 in middle but if we use i<a, it prints all the records in file.
        printf("%s/", record[i].date);
        printf("%s/", record[i].time);
        printf("%u\n", record[i].steps);
    }
   
    return 0;
}









