/**
 * @file      : task23.c
 * @brief     : Demonstrates struct copy by value behavior.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task23.c -o task23
 */

#include <stdio.h>
#include <stdlib.h>

struct DataContainer {
    int a;
};

int main(void) {
    struct DataContainer obj1 = {1};
    
    /* Direct assignments initialize complete structural copies by value */
    struct DataContainer obj2 = obj1;
    
    printf("Copied Structure obj2.a value   = %d\n", obj2.a);
    
    /* Mutating the copied struct has zero impact on the source struct object */
    obj2.a = 100;
    
    printf("Original Structure obj1.a value = %d (Should remain unchanged as 1)\n", obj1.a);
    
    return EXIT_SUCCESS;
}