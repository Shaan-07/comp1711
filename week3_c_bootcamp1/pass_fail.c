#include<stdio.h>
int main() {
    int mark;
    printf("enter your mark:\n");
    scanf("%d", &mark);
    if(mark >= 70)
    {
        printf("you got %d so you passed with distinction\n", mark);
    }
    else if(mark >= 50 && mark < 70)
    {
        printf("you got %d so you passed the test\n", mark);
    }
    else
    {
        printf("you got %d so you failed the test\n", mark);
    }
    return 0;
}