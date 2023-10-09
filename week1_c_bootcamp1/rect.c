#include<stdio.h>

int main() {
    //l is length and b is breath
    int l;
    int b;
    
    printf("enter the value of l: \n");
    scanf("%d", &l);

    printf("enter the value of b: \n");
    scanf("%d", &b);

   int ans = l * b;
// formula for area of rect is l x b and ans means answer
    printf("the area of rectangle with length %d and breath %d is %d\n", l, b, ans);

    return 0;
}