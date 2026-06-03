/**
 * @file      : task16.c
 * @brief     : Reads a string and a 1-based character index, then
 * toggles the case of the character at that position.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task16.c -o task16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 30

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
    char string[MAX_STR];
    int number;
    
    printf("Enter the word:\n");
    if (fgets(string, sizeof(string), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    // Remove trailing newline if present
    string[strcspn(string, "\r\n")] = '\0';
    int len = (int)strlen(string);
    
    printf("Enter the 1-based index to toggle: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid index pattern input.\n");
        return EXIT_FAILURE;
    }
    
    printf("\nThe original string is '%s'\n", string);
    
    if (number < 1 || number > len)
    {
        printf("Error: Index %d is out of range (string length is %d)\n", number, len);
        return EXIT_FAILURE;
    }
    
    int target_idx = number - 1;
    if (string[target_idx] >= 'a' && string[target_idx] <= 'z')
    {
        string[target_idx] -= 32;
    }
    else if (string[target_idx] >= 'A' && string[target_idx] <= 'Z')
    {
        string[target_idx] += 32;
    }
    
    printf("\nThe modified string is '%s'\n", string);
    
    return EXIT_SUCCESS;
}