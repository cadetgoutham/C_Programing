/**
 * @file      : task10.c
 * @brief     : Generates and prints an N×N grid matrix filled with sequential 
 * integers tracking a clockwise spiral execution path.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task10.c -o task10
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int array_size = 0;

    printf("Enter matrix dimension size (N): ");
    if (scanf("%d", &array_size) != 1 || array_size <= 0) {
        printf("Error: Matrix dimension must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    /* * CRITICAL SECURITY UPGRADE: Refactored VLA to dynamic heap memory.
     * Prevents Stack Overflow crashes if the user inputs large dimension sizes.
     * Memory allocation uses calloc to ensure all grid spaces initialize to 0.
     */
    int **matrix = (int **)calloc(array_size, sizeof(int *));
    if (matrix == NULL) {
        printf("System memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < array_size; i++) {
        matrix[i] = (int *)calloc(array_size, sizeof(int));
        if (matrix[i] == NULL) {
            printf("System memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    int leftAndTop = 0;
    int rightAndBottom = array_size - 1;
    int ascendingNumbers = 1;

    /* Primary Processing: Progress inward shell-by-shell */
    while (leftAndTop <= rightAndBottom) {
        
        /* 1. Fill top horizontal row (Left to Right) */
        for (int i = leftAndTop; i <= rightAndBottom; i++) {
            matrix[leftAndTop][i] = ascendingNumbers++;
        }
        
        /* 2. Fill right vertical column (Top to Bottom) */
        for (int i = leftAndTop + 1; i <= rightAndBottom; i++) {
            matrix[i][rightAndBottom] = ascendingNumbers++;
        }
        
        /* 3. Fill bottom horizontal row (Right to Left) */
        for (int i = rightAndBottom - 1; i >= leftAndTop; i--) {
            /* Guard logic protects overlapping operations on single-row scenarios */
            if (leftAndTop < rightAndBottom) {
                matrix[rightAndBottom][i] = ascendingNumbers++;
            }
        }

        /* 4. Fill left vertical column (Bottom to Top) */
        for (int i = rightAndBottom - 1; i >= leftAndTop + 1; i--) {
            /* Guard logic protects overlapping operations on single-column scenarios */
            if (leftAndTop < rightAndBottom) {
                matrix[i][leftAndTop] = ascendingNumbers++;
            }
        }

        /* Shift the operational framework boundaries inward for the next internal shell layer */
        leftAndTop++;
        rightAndBottom--;
    }

    /* Print Matrix Layout with neat spacing alignments */
    printf("\nGenerated %dx%d Spiral Matrix Layout:\n\n", array_size, array_size);
    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            printf("%-5d", matrix[i][j]);
        }
        printf("\n");
    }

    /* Dynamic Heap Cleanup Context */
    for (int i = 0; i < array_size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}