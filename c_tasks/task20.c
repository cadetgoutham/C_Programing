/**
 * @file      : task20.c
 * @brief     : Toggles the case of characters in the second half of input strings.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task20.c -o task20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUF 20

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void reverse_case_second_half(const char s[]) {
    int n = (int)strlen(s);
    int mid = n / 2;
    
    // Dynamic stack-allocated mirror variable buffer size limit allocation
    char temp[STR_BUF];
    strncpy(temp, s, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    for (int j = n; j > mid; j--) {
        int idx = j - 1;
        if (temp[idx] >= 'a' && temp[idx] <= 'z') {
            temp[idx] -= 32;
        }
        else if (temp[idx] >= 'A' && temp[idx] <= 'Z') {
            temp[idx] += 32;
        }
    }
    printf("%s -> %s\n", s, temp);
}

int main(void) {
    char str1[STR_BUF], str2[STR_BUF], str3[STR_BUF];
    char option = '\0';
    
    while (1) {
        if (option != 'x' && option != 'X') {
            printf("Enter 3 strings:\n");
            if (scanf("%19s %19s %19s", str1, str2, str3) != 3) {
                clear_input_buffer();
                continue;
            }
            reverse_case_second_half(str1);
            reverse_case_second_half(str2);
            reverse_case_second_half(str3);
        }
        else {
            break;
        }
        
        printf("\nDo you want to continue? Type x/X to terminate, or any other key to continue: ");
        if (scanf(" %c", &option) != 1) {
            break;
        }
    }
    
    printf("Exiting application runtime context.\n");
    return EXIT_SUCCESS;
}