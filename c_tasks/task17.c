/**
 * @file      : task17.c
 * @brief     : Reverses an array of character pointers pointing to elements of an array.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task17.c -o task17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /* CRITICAL BUG FIX: Appended explicit null terminator to prevent strlen crash */
    char a[] = {'a', 'b', 'c', 'd', 'e', 'f', '\0'};
    int len = (int)strlen(a);
    char *temp;
    char *ptr[6]; // Matches exact explicit dimensions
    
    for (int i = 0; i < len; i++)
    {
        ptr[i] = &a[i];
    }
    
    for (int i = 0; i < len; i++)
    {
        printf("Before: Address = %p, Value = %c\n", (void*)ptr[i], *ptr[i]);
    }
    
    for (int i = 0; i < (len / 2); i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[(len - 1) - i];
        ptr[(len - 1) - i] = temp;
    }
    
    printf("\n--- After Pointer Reversal ---\n");
    for (int i = 0; i < len; i++)
    {
        /* Fixed to display the value resolved via the pointer array */
        printf("After:  Address = %p, Value = %c\n", (void*)ptr[i], *ptr[i]);
    }
    
    return EXIT_SUCCESS;
}