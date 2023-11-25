#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

//#define buffer_size 256

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    char *inputCopy = strdup(input);
    
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }

    free(inputCopy);
}

int main() {
    FITNESS_DATA record[100];
    char line[buffer_size];
    char filename[buffer_size];
    char choice;
    int counter = 0;
    int mean = 0;
    FILE *input = NULL; // File pointer is initialized to NULL

    while (1) {
        printf("A: Specify the filename to be imported - you need to check that the file opened correctly.\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: View your lowest blood iron level\n");                     
        printf("D: View your highest blood iron level\n");                    
        printf("E: View the blood iron levels for a specific month\n");       
        printf("F: See some additional statistics about your iron levels\n"); 
        printf("G: Generate a graph of your iron levels\n");                  
        printf("Q: Exit the program\n");

        choice = getchar();
        while (getchar() != '\n');

        switch (choice) {
            case 'A':
            case 'a':
                if (input != NULL) {
                    fclose(input); // Close the previous file if it's open
                }
                printf("Input filename: ");
                fgets(line, buffer_size, stdin);
                sscanf(line, " %s ", filename);

                input = fopen(filename, "r");
                if (!input) {
                    printf("Error: File could not be opened\n");
                    return 1;
                }
                // Reset the counter when a new file is opened
                counter = 0;
                while (fgets(line, buffer_size, input) != NULL) {
                    char date[11];
                    char time[6]; 
                    char steps[10];
                    tokeniseRecord(line, ",", date, time, steps);
                    strncpy(record[counter].date, date, sizeof(record[counter].date));
                    strncpy(record[counter].time, time, sizeof(record[counter].time));
                    record[counter].steps = atoi(steps);
                    counter++;
                }
                break;

            case 'B':
            case 'b':
                printf("Total records: %i\n", counter);
                break;

            // Add other cases for menu options 'C' to 'G' and 'Q' as needed

            case 'Q':
            case 'q':
                if (input != NULL) {
                    fclose(input); // Close the file before exiting
                }
                return 0;
        }
    }
    return 0;
}

