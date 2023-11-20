#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int arrayA[3][4];
  int i, j;
    srand(time(NULL));
  
  for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            arrayA[i][j] = rand() % 11; // rand() % 11 gives a range 0 to 10
        }
  }
  for(i = 0; i < 3; i++) {
        for(j = 0; j < 4; j++) {
            printf("%d ", arrayA[i][j]);
        }
        printf("\n");
    }

    return 0;
}
