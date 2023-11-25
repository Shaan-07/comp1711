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
    //int mean = 0;
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
            case 'C':
            case 'c':
                if (counter > 0) {
                    int minStepsIndex = 0;
                    for (int i = 1; i < counter; i++) {
                        if (record[i].steps < record[minStepsIndex].steps) {
                            minStepsIndex = i;
                        }
                    }
                    printf("Date and time of the timeslot with the fewest steps: %s %s\n", record[minStepsIndex].date, record[minStepsIndex].time);
                } else {
                    printf("No records available.\n");
                }
                break;

            case 'D':
            case 'd':
                if (counter > 0) {
                    int maxStepsIndex = 0;
                    for (int i = 1; i < counter; i++) {
                        if (record[i].steps > record[maxStepsIndex].steps) {
                            maxStepsIndex = i;
                        }
                    }
                    printf("Date and time of the timeslot with the highest number of steps: %s %s\n", record[maxStepsIndex].date, record[maxStepsIndex].time);
                } else {
                    printf("No records available.\n");
                }
                break;

            case 'E':
            case 'e':
                if (counter > 0) {
                    double mean = 0.0;
                    for (int i = 0; i < counter; i++) {
                        mean += record[i].steps;
                    }
                    mean /= counter;

                    // Check for fractional part
                    int roundedMean = (mean - (int)mean) > 0 ? (int)mean + 1 : (int)mean;

                    printf("Mean step count of the records: %d\n", roundedMean);
                } else {
                    printf("No records available.\n");
                }
                break;

            case 'F':
case 'f':
    if (counter > 0) {
        int longestPeriodStart = -1;
        int longestPeriodEnd = -1;
        int currentPeriodStart = -1;

        for (int i = 0; i < counter; i++) {
            if (record[i].steps > 500) {
                if (currentPeriodStart == -1) {
                    currentPeriodStart = i;
                }
            } else {
                if (currentPeriodStart != -1) {
                    // Check if the current period is longer than the longest recorded
                    if ((longestPeriodStart == -1) || (i - currentPeriodStart > longestPeriodEnd - longestPeriodStart)) {
                        longestPeriodStart = currentPeriodStart;
                        longestPeriodEnd = i;
                    }
                    currentPeriodStart = -1;
                }
            }
        }

        // Check if the last period is longer than the longest recorded
        if ((currentPeriodStart != -1) && (counter - currentPeriodStart > longestPeriodEnd - longestPeriodStart)) {
            longestPeriodStart = currentPeriodStart;
            longestPeriodEnd = counter;
        }

        if (longestPeriodStart != -1) {
            printf("Longest period start: %s %s\n", record[longestPeriodStart].date, record[longestPeriodStart].time);
            printf("Longest period end: %s %s\n", record[longestPeriodEnd - 1].date, record[longestPeriodEnd - 1].time);
        } else {
            printf("No period found where the step count is above 500.\n");
        }
    } else {
        printf("No records available.\n");
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

