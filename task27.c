/**
 * @file      : task27.c
 * @brief     : Demonstrates explicit structural brace initializer assignment paradigms.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task27.c -o task27
 */

#include <stdio.h>
#include <stdlib.h>

struct person {
    char name[25];
    char city[15];
};

int main(void) {
    struct person p = {"Hilton", "SanJose"};
    printf("Person Details: %s, %s\n", p.name, p.city);
    return EXIT_SUCCESS;
}