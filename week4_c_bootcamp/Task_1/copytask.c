#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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
    char filename[] = "FitnessData_2023.csv";//code idea from read_from_file.c code done in lab session.
    FILE *file = fopen(filename, "r");// or "a", "w+", "a+", "r+"
    if (file == NULL) {
        perror("");
        return 1;
    }

    int buffer_size = 1000;
    char line_buffer[buffer_size];
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        FITNESS_DATA record[1000];// here we are creating an array Martin sir.
        int a = 0; 
        char my_date[11];
        char my_time[6]; // Increased the size by 1 for null terminator
        char my_steps[8];
        tokeniseRecord(line_buffer,",",my_date, my_time, my_steps);
    
    

    }
    // Always close your file or c will chew your face off.
    fclose(file);

    for (int i = 0; i < 3; i++) {
        printf("%s/", record[i].date);
        printf("%s/", record[i].time);
        printf("%u\n", record[i].steps);
    }
return 0;
}
