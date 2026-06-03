/**
 * @file      : task29.c
 * @brief     : Showcases a tagged union layout bounded by macro tracking flags.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task29.c -o task29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_NAME   1
#define F_AGE    2
#define F_SALARY 3

union employee {
    char name[30];
    int age;
    float salary;
};

struct emp_details {
    union employee emp;
    unsigned char flag;
} E;

void print_val(const struct emp_details *t_emp) {
    switch (t_emp->flag) {
        case F_NAME:
            printf("\nNAME = %s\n", t_emp->emp.name);
            break;
            
        case F_AGE:
            printf("\nAGE = %d\n", t_emp->emp.age);
            break;
            
        case F_SALARY:
            printf("\nSALARY = %.2f\n", t_emp->emp.salary);
            break;
        default:
            printf("\nUnknown state configuration context.\n");
            break;
    }
}

int main(void) {
    /* Upgraded to safe bounded copy patterns */
    strncpy(E.emp.name, "ANAND", sizeof(E.emp.name) - 1);
    E.emp.name[sizeof(E.emp.name) - 1] = '\0';
    
    E.flag = F_NAME;
    struct emp_details *ptr = &E;
    print_val(ptr);
    
    return EXIT_SUCCESS;
}