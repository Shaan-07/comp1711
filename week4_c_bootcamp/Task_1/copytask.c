#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

int main() {
    // Open the CSV file for reading
    FILE* file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Define an array to store the data
    FITNESS_DATA record[100]; // Assuming a maximum of 100 record in the CSV

    int count = 0; // Counter for the number of records read

    // Read and store data from the CSV
    while (fscanf(file, "%19[^,],%19[^,],%d\n", record[count].date, &record[count].time, record[count].steps) == 3) {
        count++;
    }

    // Close the file
    fclose(file);

    // Print the data
    for (int i = 0; i < count; i++) {
        printf("record %d: date: %s, time: %s, steps: %u\n", i + 1, record[i].date, record[i].time, record[i].steps);
    }

    return 0;
}
