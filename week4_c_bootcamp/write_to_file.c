#include <stdio.h>

int main() {
    char filename[] = "data.txt";
    FILE *file = fopen(filename, "w");// or "a", "w+", "a+", "r+"
    if (file == NULL) {
        perror("");
        return 1;
    }
    int numbers, num_lines = 10;
    printf("type %d numbers:", num_lines);
    for (int i = 0; i < num_lines; i++) {
        scanf("%d", &numbers);
        fprintf(file, "%d\n", numbers);
        }

    fclose(file);
    return 0;
    }