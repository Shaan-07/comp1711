#include<stdio.h>
int main() {
    int mark=39;
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