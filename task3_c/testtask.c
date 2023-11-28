#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

// Function to compare two FitnessData records for sorting in descending order of steps
//int compareRecords(const void *a, const void *b) {
    //return ((FitnessData *)b)->steps - ((FitnessData *)a)->steps;
//}
int compareRecords(const void *a, const void *b) {
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

    // Read data into a fixed-size array
    #define MAX_RECORDS 1000
    FitnessData data[MAX_RECORDS];
    int count = 0;

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (count < MAX_RECORDS) {
            tokeniseRecord(line, ',', data[count].date, data[count].time, &data[count].steps);
            count++;
        } else {
            printf("Error: too many records in the file\n");
            break;
        }
    }

    fclose(file);

    // Step 3: Sort the data in descending order of steps
    qsort(data, count, sizeof(FitnessData), compareRecords);

    // Step 4: Write out the sorted data file
    strcat(filename, ".tsv");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: cannot create output file\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);

    return 0;
}
