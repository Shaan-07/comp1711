#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    char choice;
    int counter = 0;
    int MinStep = 0;
    int MaxStep = 0;
    double mean = 0.0;
    int Start = -1;
    int End = -1;
    int CurrentStart = -1;
    FILE *input = NULL; // File pointer is initialized to NULL

    while (1) {
        printf("A: Specify the filename to be imported - you need to check that the file opened correctly.\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");                     
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");                    
        printf("E: Find the mean step count of all the records in the file\n");       
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");                   
        printf("Q: Exit\n");

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
        
            case 'C':
            case 'c':
                if (counter > 0) {
                    for (int i = 1; i < counter; i++) {
                        if (record[i].steps < record[MinStep].steps) {
                            MinStep = i;
                        }
                    }
                    printf("Fewest steps: %s %s\n", record[MinStep].date, record[MinStep].time);
                } 
                break;

            case 'D':
            case 'd':
                if (counter > 0) {
                    for (int i = 1; i < counter; i++) {
                        if (record[i].steps > record[MaxStep].steps) {
                            MaxStep = i;
                        }
                    }
                    printf("Largest steps: %s %s\n", record[MaxStep].date, record[MaxStep].time);
                } 
                break;

            case 'E':
            case 'e':
                if (counter > 0) {
                    for (int i = 0; i < counter; i++) {
                        mean += record[i].steps;
                    }
                    mean /= counter;

                    // Check for fractional part
                    int roundedMean = (mean - (int)mean) > 0 ? (int)mean + 1 : (int)mean;

                    printf("Mean step count: %d\n", roundedMean);
                }
                break;


            case 'F':
            case 'f':
            if (counter > 0) {

            for (int i = 0; i < counter; i++) {
                if (record[i].steps > 500) {
                    if (CurrentStart == -1) {
                        CurrentStart = i;
                    }
                } else {
                    if (CurrentStart != -1) {
                        // Check if the current period is longer than the longest recorded
                        if ((Start == -1) || (i - CurrentStart > End - Start)) {
                            Start = CurrentStart;
                            End = i;
                        }
                        CurrentStart = -1;
                    }
                }
            }

        // Check if the last period is longer than the longest recorded
        if ((CurrentStart != -1) && (counter - CurrentStart > End - Start)) {
            Start = CurrentStart;
            End = counter;
        }

        if (Start != -1) {
            printf("Longest period start: %s %s\n", record[Start].date, record[Start].time);
            printf("Longest period end: %s %s\n", record[End - 1].date, record[End - 1].time);
        } 
    }
    break;


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