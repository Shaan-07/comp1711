#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness record
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to validate and tokenize a record
int validateAndTokenizeRecord(char *record, FitnessData *data) {
    int result = sscanf(record, "%10[^,],%5[^,],%d", data->date, data->time, &data->steps);

    // Check for the correct number of conversions (3) and a non-negative steps value
    if (result == 3 && data->steps >= 0) {
        return 1; // Valid record
    } else {
        return 0; // Invalid record
    }
}

// Function to compare two FitnessData records for sorting in descending order of steps
int compareRecords(const void *a, const void *b) {
    const FitnessData *recordA = (const FitnessData *)a;
    const FitnessData *recordB = (const FitnessData *)b;

    return (recordB->steps > recordA->steps) - (recordB->steps < recordA->steps);
}

int main() {
    char filename[100];
    int count = 0;
    char line[100];

    // Asking for user input
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    // Checking if the file is empty or not
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: empty file\n");
        fclose(file);
        return 1;
    }

    // Reopen the file
    fclose(file);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    // Read record into a fixed-size array
    #define buffer_size 1000
    FitnessData record[buffer_size];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count < buffer_size) { // Checks for invalid format
            if (!validateAndTokenizeRecord(line, &record[count])) {
                printf("Error: invalid format\n");
                fclose(file);
                return 1;
            }
            count++;
        } else {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    // Sort the record in descending order of steps
    qsort(record, count, sizeof(FitnessData), compareRecords);

    // Outputting data to a new file
    strcat(filename, ".tsv");
    file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", record[i].date, record[i].time, record[i].steps);
    }

    fclose(file);
    printf("Data sorted and returned to: %s\n", filename);

    return 0;
}





