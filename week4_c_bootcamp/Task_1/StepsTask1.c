#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	unsigned steps;
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
    
FITNESS_DATA record[100];// here we are creating an array Martin sir.
    int a = 0; 

    // I used a little bit of internet to understand the use of fscanf function.
    while (fscanf(file, "%[^,],%[^,],%d\n", record[a].date, record[a].time, &record[a].steps) == 3) {
        a++;
    }

    // Always close your file or c will chew your face off.
    fclose(file);

    printf("Number of records in file: %i\n", a);

    for (int i = 0; i < a; i++) {
        printf("-------------\n");
        //printf("Record: %s\n");
        printf("%s/", record[i].date);
        printf("%s/", record[i].time);
        printf("%u\n", record[i].steps);
    }
    printf("-------------\n");
   
    return 0;
}
