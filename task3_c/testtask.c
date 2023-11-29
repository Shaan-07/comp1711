#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness record
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
int tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
                return 1; // Successfully parsed all three sections
            }
        }
    }

    // If any section is missing, return 0 to indicate incorrect format
    return 0;
}

// Function to compare two FitnessData records for sorting in descending order of steps
int NewRecord(const void *a, const void *b) {
    const FitnessData *recordA = (const FitnessData *)a;
    const FitnessData *recordB = (const FitnessData *)b;

    for (int i = 0; i < sizeof(FitnessData) / sizeof(int); i++) {
        if (recordB->steps != recordA->steps) {
            return recordB->steps - recordA->steps;
        }
    }
    return 0;
}

int main() {
    char filename[100];
    int count = 0;
    char line[100];

    // Step 1: Ask the user for a filename
    printf("Enter filename: ");
    scanf("%s", filename);

    // Step 2: Open and read the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // File does not exist or cannot be opened
        printf("Error: invalid file\n");
        return 1;
    }

    // Read record into a fixed-size array
    #define buffer_size 1000
    FitnessData record[buffer_size];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count < buffer_size) {
            if (!tokeniseRecord(line, ',', record[count].date, record[count].time, &record[count].steps)) {
                printf("Error: invalid format\n");
                fclose(file);
                return 1;
            }
            count++;
        } else {
            printf("Error: too many records in the file\n");
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    // Step 3: Sort the record in descending order of steps
    qsort(record, count, sizeof(FitnessData), NewRecord);

    // Step 4: Write out the sorted record file
    strcat(filename, ".tsv");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: cannot create output file\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", record[i].date, record[i].time, record[i].steps);
    }

    fclose(file);

    return 0;
}

