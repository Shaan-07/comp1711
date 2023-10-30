#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
     char filename[] = "FitnessData_2023.csv";//code idea from read_from_file.c code done in lab session.
    FILE *file = fopen(filename, "r");// or "a", "w+", "a+", "r+"
    if (file == NULL) {
        perror("");
        return 1;
    }
    int buffer_size = 100;
    char line_buffer[buffer_size];
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        printf("%s", line_buffer);
    }



    char record[21] = {};
    char date[11];
    char time[6];
    char steps[10];  // Large enough to hold a typical step count as a string

    int stepsint;
    
    tokeniseRecord(record, ",", date, time, steps);
    
    printf("Date: %s\n", date);
    printf("Time: %s\n", time);
    printf("Steps: %s\n", steps);

    // Convert the steps string to an integer
    stepsint = atoi(steps);
    printf("Steps as an integer: %d\n", stepsint);
    
    return 0;
}
