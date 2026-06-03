/**
 * @file      : task25.c
 * @brief     : Collects dynamic records and evaluates average running metrics.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task25.c -o task25
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct employee_details {
    char name[20];
    char address[50];
    int age;
    float salary;
} emp;

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int n;
    double average = 0.0;

    printf("Enter the number of records to track: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid record count value.\n");
        return EXIT_FAILURE;
    }

    /* Heap memory allocation safeguard */
    emp *person = (emp *)calloc(n, sizeof(emp));
    if (person == NULL) {
        printf("Memory allocation failure.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Record Entry [%d of %d] ---\n", i + 1, n);
        printf("Name: ");
        scanf("%19s", person[i].name);

        printf("Address: ");
        scanf("%49s", person[i].address);

        printf("Age: ");
        while (scanf("%d", &person[i].age) != 1) {
            printf("Invalid age. Re-enter: ");
            clear_input_buffer();
        }

        printf("Salary: ");
        while (scanf("%f", &person[i].salary) != 1) {
            printf("Invalid salary value. Re-enter: ");
            clear_input_buffer();
        }
    }

    for (int i = 0; i < n; i++) {
        average += person[i].salary;
    }
    average = average / n;

    printf("\nThe average salary across %d employees is: %.2f\n", n, average);

    free(person);
    return EXIT_SUCCESS;
}