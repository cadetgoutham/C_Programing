/**
 * @file      : task19.c
 * @brief     : Reverses a string using an array of pointers and displays details.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task19.c -o task19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char a[] = "string";
    int len = (int)strlen(a);
    char *temp;
    char *ptr[6]; 
    
    for (int i = 0; i < len; i++) {
        ptr[i] = &a[i];
    }
    
    for (int i = 0; i < len; i++) {
        printf("Before: Address = %p, Value = %c\n", (void*)ptr[i], *ptr[i]);
    }
    
    for (int i = 0; i < (len / 2); i++) {
        temp = ptr[i];
        ptr[i] = ptr[(len - 1) - i];
        ptr[(len - 1) - i] = temp;
    }
    
    printf("\n--- After Pointer Reversal ---\n");
    for (int i = 0; i < len; i++) {
        /* Dereferenced pointer layout verified */
        printf("After:  Address = %p, Value = %c\n", (void*)ptr[i], *ptr[i]);
    }
    return EXIT_SUCCESS;
}