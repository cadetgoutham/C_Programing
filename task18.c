/**
 * @file      : task18.c
 * @brief     : Validates a user-supplied name and phone number against hardcoded credentials.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task18.c -o task18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char name[100];
    char number[20];

    printf("Enter name and number:\n");
    /* CRITICAL SAFETY UPGRADE: Added width boundaries to block string overflows */
    if (scanf("%99s %19s", name, number) != 2) {
        printf("Input collection failure.\n");
        return EXIT_FAILURE;
    }

    if ((strcmp(name, "username") == 0) && (strcmp(number, "1234567890") == 0))
    {
        printf("  INPUT VALID  \n");
    }
    else
    {
        printf("  INPUT INVALID  \n");
    }

    return EXIT_SUCCESS;
}