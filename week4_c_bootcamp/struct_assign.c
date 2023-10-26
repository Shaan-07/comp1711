#include <stdio.h>
#include <string.h>

struct student {
    char name [20];
    char student_id [11];
    unsigned mark;
};
int main() {
    struct student a;
    strcpy(a.name, "Shaan Shaikh");
    strcpy(a.student_id, "201803653");
    a.mark=70;
    printf("name:%sa\n", a.name);
    printf("id:%s\n", a.student_id);
    printf("marks:%u\n", a.mark);
    return 0;
}