/**
 * @file      : task8.c
 * @brief     : Collects a fixed array of single characters from user inputs
 * and outputs them sequentially back to the terminal screen.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task8.c -o task8
 */

#include <stdio.h>
#include <stdlib.h>

/* Standardized Configuration: Symbolic macro to eliminate magic number dependencies */
#define CHAR_COUNT 5

int main(void) {
    char characters[CHAR_COUNT];

    printf("Enter %d characters individually:\n", CHAR_COUNT);

    /* Phase 1: Interactive Data Aggregation */
    for (int i = 0; i < CHAR_COUNT; i++) {
        printf("Character [%d]: ", i);
        
        /* * CRITICAL FIX: Changed from "%s" to " %c". 
         * The leading space in " %c" tells scanf to automatically discard 
         * preceding whitespace and trailing newline characters (\n) left in the buffer.
         */
        if (scanf(" %c", &characters[i]) != 1) {
            printf("Error reading input configuration state.\n");
            return EXIT_FAILURE;
        }
    }

    printf("\nDisplaying characters:\n");

    /* Phase 2: Array Layout Output Formatting */
    for (int i = 0; i < CHAR_COUNT; i++) {
        printf("%c\n", characters[i]);
    }

    return EXIT_SUCCESS;
}