#include<stdio.h>
int main() {
    int a;
    printf("enter the number:\n");
    scanf("%d", &a);

    if(a == 0)
    {
        printf("you entered %d which is zero\n", a);
    }
    else if(a > 0)
    {
        printf("you entered %d which is positive\n", a);
    }
    else 
    {
        printf("you entered %d which is negitive\n", a);
    }
    return 0;
}