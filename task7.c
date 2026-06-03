/**
 * @file      : task7.c
 * @brief     : Collects an array of integers from user inputs and outputs 
 * them sequentially back to the terminal screen.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task7.c -o task7
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Standardized Configuration: Symbolic constant to eliminate magic numbers */
#define ARRAY_SIZE 5

/**
 * @brief Flushes residual characters out of standard input streams to avoid input bugs.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int values[ARRAY_SIZE];

    printf("Enter %d integers:\n", ARRAY_SIZE);

    /* Phase 1: Interactive Data Aggregation with Input Verification */
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Element [%d]: ", i);
        while (scanf("%d", &values[i]) != 1) {
            printf("Format Anomaly! Please input a valid integer for element [%d]: ", i);
            clear_input_buffer();
        }
    }

    printf("\nDisplaying integers:\n");

    /* Phase 2: Array Layout Output Formatting */
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d\n", values[i]);
    }

    return EXIT_SUCCESS;
}