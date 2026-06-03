/**
 * @file      : task28.c
 * @brief     : Inspects system layout profiles and structural padding configurations.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task28.c -o task28
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    char B;
    char C;
} InfoData;

typedef struct {
    double D;
    char c;
    InfoData I;
} recordData;

int main(int argc, char *argv[])
{
    (void)argc; /* Suppress unused flag compiler warnings */
    (void)argv;

    /* Upgraded to %zu for unified standard portability checks on structural dimensions */
    printf("\nSize of InfoData Struct   = %zu bytes\n", sizeof(InfoData));
    printf("Size of recordData Struct = %zu bytes\n\n", sizeof(recordData));
    
    return EXIT_SUCCESS;
}