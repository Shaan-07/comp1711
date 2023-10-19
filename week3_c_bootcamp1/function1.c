#include<stdio.h> 

float sum(float a, float b)
{
    float answer;
    answer = a + b;
    return answer;
}

int main()
{
    float y = 2.5678;
    float z = sum(5, y); // calling our new function
    
    printf("the sum of 5 and %g is %.2f\n", y, z);
}