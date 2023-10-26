#include <stdio.h>

struct student {
    char name [20];
    char student_id [11]; // assuming upto 10 digits
    unsigned mark;
};
int main() 
    struct student new_student = {"Shaan Shaikh", "201803653", 19};// 'new_student' is just a variable and is changable by any other variable
    printf("name:%s\n", new_student.name);
    printf("id:%s\n", new_student.student_id);
    printf("marks:%u\n", new_student.mark);
    //variable.struct is used to call the structure field
    return 0;
}