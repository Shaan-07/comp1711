#include<stdio.h>
int main() {
    int mark;
    printf("enter your marks:\n");
    scanf("%d", &mark);
    if(mark == 0)
    {
        printf("the mark of %d is zero\n", mark);
    }
    else if(mark > 40)
    {
        printf("the mark of %d is pass\n", mark);
    }
    else
    {
        printf("you got %d so you are an idiot\n", mark);
    }
    return 0;
}