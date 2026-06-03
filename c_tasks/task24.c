/**
 * @file      : task24.c
 * @brief     : Collects employee records into a structural array and sorts 
 * them by ID number using an optimized bubble sort algorithm.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task24.c -o task24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMP_COUNT 5

typedef struct details {
    int number;
    char f_name[30];
    char s_name[30];
} emp;

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void sorting(emp list[], int size)
{
    emp temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < (size - 1 - i); j++)
        {
            if (list[j].number > list[j + 1].number)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}

int main(void)
{
    emp person[EMP_COUNT];

    for (int i = 0; i < EMP_COUNT; i++) {
        printf("--- Record Entry [%d of %d] ---\n", i + 1, EMP_COUNT);
        printf("Enter Employee ID Number: ");
        while (scanf("%d", &person[i].number) != 1) {
            printf("Invalid number format. Re-enter: ");
            clear_input_buffer();
        }

        printf("Enter First Name: ");
        /* Width-limited to size - 1 to protect storage boundaries */
        while (scanf("%29s", person[i].f_name) != 1) {
            clear_input_buffer();
        }

        printf("Enter Second Name: ");
        while (scanf("%29s", person[i].s_name) != 1) {
            clear_input_buffer();
        }
    }

    /* Sort the database */
    sorting(person, EMP_COUNT);

    printf("\n--- Sorted Employee Database Record Details ---\n");
    for (int i = 0; i < EMP_COUNT; i++) {
        printf("ID: %-5d | Name: %s %s\n", person[i].number, person[person[i].number ? i : i].f_name, person[i].s_name);
    }

    return EXIT_SUCCESS;
}