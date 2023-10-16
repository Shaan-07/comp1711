#include<stdio.h>
int main() {
    int a;
    printf("enter the number:\n");
    scanf("%d", &a);
    if(a % 4 == 0 && a % 5 == 0)
    {
        printf("%d is divisible by both 4 & 5\n", a);
    }
    else
    {
        printf("%d is either not divisible by 4 or 5\n", a);
    }
    return 0;
}