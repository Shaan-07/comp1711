#include<stdio.h>
int main() {
    int a;
    a = 1;

    switch (a)
    {
        case 0: printf("option 0 has been selected\n");
        break;
        case 1: printf("option 1 has been selected\n");
        break;
        default: printf("a different option had been selected\n");
    }
}