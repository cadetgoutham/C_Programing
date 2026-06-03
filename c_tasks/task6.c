/**
 * @file      : task6.c
 * @brief     : A clean, standard-compliant iteration module that leverages 
 * a structured for loop to print numbers sequentially from 1 to 10.
 * @note      : Compiles cleanly under standard flags: gcc -Wall -Wextra -std=c99 task6.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    /* * Standardized C99 Loop Profile: Variable declaration, conditional boundary check, 
     * and step accumulation expression logic are packaged neatly in the loop header.
     */
    for (int itr = 1; itr <= 10; itr++) {
        printf("%d\n", itr);
    }

    printf("\nEnd of loop\n");

    return EXIT_SUCCESS;
}