#include<stdio.h>
int main() {
    int mark;
    printf("enter your marks:\n");
    scanf("%d", &mark);
    printf("the marks to be checked is:%d\n", mark);
    if(mark >= 0 && mark <= 100)
    {
        if(mark == 0)
        {
            printf("you got %d so u should die\n", mark);
        }
        else if(mark > 40)
        {
            printf("you got %d so you must be a genius\n", mark);
        }
        else
        {
            printf("you got %d so you are an idiot\n", mark);
        }
    }
    else
    {
        printf("%d is not between 0 and 100\n", mark);
    }
    return 0;
}