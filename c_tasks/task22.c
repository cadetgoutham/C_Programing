/**
 * @file      : task22.c
 * @brief     : Demonstrates struct designated initializers in C.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task22.c -o task22
 */

#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x, y, z;
}; 

int main(void)
{
    /* Designated initializers keep field mapping flexible regardless of ordering changes */
    struct Point p1 = {.y = 0, .z = 1, .x = 2};
    printf("%d %d %d\n", p1.x, p1.y, p1.z);
    
    return EXIT_SUCCESS;
}