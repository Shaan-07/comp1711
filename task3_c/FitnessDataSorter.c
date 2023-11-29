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
                return 1; //this checks for that all the sections are present
            }
        }
    }

    //if any section is missing, return 0 and exit
    return 0;
}

//this function is used compare records for sorting in descending order of steps
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

    //asking for user input
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    //checking if the file is empty or not
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: empty file\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    //reoprn the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    //read record into a fixed-size array
    #define buffer_size 1000
    FitnessData record[buffer_size];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count < buffer_size) {//checks for invalid format
            if (!tokeniseRecord(line, ',', record[count].date, record[count].time, &record[count].steps)) {
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

    //sort the record in descending order of steps(used internet for this method)
    qsort(record, count, sizeof(FitnessData), NewRecord);

    //outputting data in new file
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
