/**
 * @file      : task12.c
 * @brief     : Tracks sequential allocation inputs inside a bounded buffer tracking system,
 * printing proportional data volume warning thresholds dynamically.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task12.c -o task12
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

/**
 * @brief Flushes any residual garbage characters out of standard terminal input stream buffers.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Inserts a tracking item into the storage array and prints allocation thresholds.
 * @param key The integer payload value to store inside the array buffer index.
 * @param target_storage Pointer to the target destination array storage space.
 */
void process_buffer_warnings(int key, int *target_storage) {
    static int internal_index = 0;

    /* SECURITY DEFENSE: Prevent execution bounds violations if the buffer limit is breached */
    if (internal_index >= SIZE) {
        printf("\nWarning Event Blocked: Memory allocation boundaries breached. Operation dropped.\n");
        return;
    }

    /* Assign payload data securely to the local element pointer offset */
    target_storage[internal_index] = key;
    
    /* Calculate current data layout metrics sequentially */
    int current_element_count = internal_index + 1;

    /* * ADAPTIVE THRESHOLD MATH:
     * Calculates percentages dynamically based on cross-multiplication, 
     * making it immune to integer truncation bugs if the macro SIZE changes.
     */
    if (current_element_count * 5 == SIZE) {          /* 1/5th filled = 20% */
        printf("\n>>> [ALERT: LOW CAPACITY REACHED (20%%)] <<<\n\n");
    } 
    else if (current_element_count * 5 == SIZE * 2) { /* 2/5ths filled = 40% */
        printf("\n>>> [ALERT: MEDIUM CAPACITY REACHED (40%%)] <<<\n\n");
    } 
    else if (current_element_count * 5 == SIZE * 4) { /* 4/5ths filled = 80% */
        printf("\n>>> [WARNING: HIGH CAPACITY ALERT (80%%)] <<<\n\n");
    } 
    else if (current_element_count == SIZE) {         /* Fully filled = 100% */
        printf("\n>>> [CRITICAL: SYSTEM STORAGE FULL (100%%)] <<<\n\n");
    }

    internal_index++;
}

int main(void) {
    int local_buffer[SIZE];
    int user_input_item = 0;

    printf("--- Bounded Data Matrix Monitoring Engine Initialization ---\n\n");

    for (int loop_index = 0; loop_index < SIZE; loop_index++) {
        printf("Enter item value for Element [%d of %d]: ", loop_index + 1, SIZE);
        
        while (scanf("%d", &user_input_item) != 1) {
            printf("Format Anomaly! Provide a valid integer token configuration: ");
            clear_input_buffer();
        }
        
        process_buffer_warnings(user_input_item, local_buffer);
    }

    return EXIT_SUCCESS;
}