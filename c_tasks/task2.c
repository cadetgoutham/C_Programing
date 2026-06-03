/**
 * @file      : task2.c
 * @brief     : A highly robust, crash-safe Logic Gate Simulator. Accepts a 
 * gate operational symbol (&, |, !, *, +, ^) and performs 
 * proper bitwise evaluations on strictly enforced binary states.
 * @note      : Compiles cleanly with standard C flags: gcc -Wall -Wextra -std=c11
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Flushes leftover residual data out of standard entry buffer streams.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Captures a single input and validates that it is strictly binary (0 or 1).
 * @return A validated binary integer value.
 */
int get_binary_input(const char *prompt) {
    int value;
    while (true) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && (value == 0 || value == 1)) {
            return value;
        }
        printf("Invalid configuration state! Values must be strictly 0 or 1.\n");
        clear_input_buffer();
    }
}

void run_gate_simulation(char gate) {
    int num_1, num_2;
    int iterations = (gate == '!') ? 2 : 4;

    printf("\n--- Processing Truth Table Sequence (%d Iterations Required) ---\n", iterations);
    
    for (int temp = 0; temp < iterations; temp++) {
        printf("\n[Iteration %d of %d]\n", temp + 1, iterations);
        
        if (gate == '!') {
            num_1 = get_binary_input("Enter Binary Input A (0 or 1): ");
            /* Logical NOT operator (!) naturally converts 1->0 and 0->1 */
            printf("RESULT -> NOT Gate (!%d) = %d\n", num_1, !num_1);
        } else {
            num_1 = get_binary_input("Enter Binary Input A (0 or 1): ");
            num_2 = get_binary_input("Enter Binary Input B (0 or 1): ");
            
            switch (gate) {
                case '&':
                    printf("RESULT -> AND Gate (%d & %d) = %d\n", num_1, num_2, num_1 & num_2);
                    break;
                case '|':
                    printf("RESULT -> OR Gate (%d | %d) = %d\n", num_1, num_2, num_1 | num_2);
                    break;
                case '*':
                    /* Proper NAND: Bitwise AND, inverted, then mask-isolated to 1 bit */
                    printf("RESULT -> NAND Gate (%d NAND %d) = %d\n", num_1, num_2, (~(num_1 & num_2)) & 1);
                    break;
                case '+':
                    /* Proper NOR: Bitwise OR, inverted, then mask-isolated to 1 bit */
                    printf("RESULT -> NOR Gate (%d NOR %d) = %d\n", num_1, num_2, (~(num_1 | num_2)) & 1);
                    break;
                case '^':
                    printf("RESULT -> XOR Gate (%d ^ %d) = %d\n", num_1, num_2, num_1 ^ num_2);
                    break;
            }
        }
    }
}

int main(void) {
    char gate;

    while (true) {
        printf("\n=================================");
        printf("\n       LOGIC GATE SIMULATOR      ");
        printf("\n=================================\n");
        printf("& for AND Gate\n"
               "| for OR Gate\n"
               "! for NOT Gate\n"
               "* for NAND Gate\n"
               "+ for NOR Gate\n"
               "^ for XOR Gate\n"
               "x to Exit Application\n"
               "Select Operational Vector: ");
        
        if (scanf(" %c", &gate) != 1) {
            clear_input_buffer();
            continue;
        }

        if (gate == 'x' || gate == 'X') {
            printf("Exiting simulator engine workflow...\n");
            exit(EXIT_SUCCESS);
        }

        if (gate == '&' || gate == '|' || gate == '!' || gate == '*' || gate == '+' || gate == '^') {
            run_gate_simulation(gate);
        } else {
            printf("\nError: Unknown operational matrix choice token symbol.\n");
            clear_input_buffer();
        }
    }

    return 0;
}