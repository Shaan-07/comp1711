#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a typedef struct for the record
typedef struct {
    char date[20];
    char time[20];
    int steps;
} FITNESS_DATA;

int main() {
    // Open the CSV file for reading
    FILE* file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Define an array to store the record
    FITNESS_DATA record[100]; // Assuming a maximum of 100 record points in the CSV

    int a = 0; // Counter for the number of records read

    // Read and store record from the CSV
    while (fscanf(file, "%[^,],%[^,],%d\n", record[a].date, record[a].time, &record[a].steps) == 3) {
        a++;
    }

    // Close the file
    fclose(file);

    // Print the record
    for (int i = 0; i < a; i++) {
        printf("record %d: Date: %s, Time: %s, Steps: %d\n", i + 1, record[i].date, record[i].time, record[i].steps);
    }
    printf("total records: %i\n", a);

    return 0;
}
