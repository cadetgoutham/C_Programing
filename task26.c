/**
 * @file      : task26.c
 * @brief     : Demonstrates standard declaration context and tracking signatures.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task26.c -o task26
 */

#include <stdio.h>
#include <stdlib.h>

struct decl {
    int n;
} d1;

int main(void) 
{
    d1.n = 100;
    printf("Global Struct Value: %d\n", d1.n);
    return EXIT_SUCCESS;
}