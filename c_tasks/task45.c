/**
  * @file      : task45.c
  * @brief     : Swaps the upper and lower nibbles (4-bit halves) of an 8-bit
  * hexadecimal byte using bitwise operations.
  */

#include <stdio.h>
 
int main(void)
{
    int original_input;
    
    printf("Enter the input:\n");
    // Read input from user as a hexadecimal value
    scanf("%x", &original_input);
    
    printf("\nBefore swapping the bit : %x\n", original_input);
    
    /* * 1. (original_input & 0x0F) << 4
     * Isolates the lower 4 bits (e.g., 0x0A becomes 0x0A) 
     * and shifts them left by 4 positions to become the upper nibble (0xA0).
     *
     * 2. (original_input & 0xF0) >> 4
     * Isolates the upper 4 bits (e.g., 0x30 becomes 0x30)
     * and shifts them right by 4 positions to become the lower nibble (0x03).
     *
     * 3. The bitwise OR (|) operator combines the two shifted components.
     */
    int isolated_lower_nibble = (original_input & 0x0F) << 4;
    int isolated_upper_nibble = (original_input & 0xF0) >> 4;
    int swapped_result        = isolated_lower_nibble | isolated_upper_nibble;
    
    printf("\nAfter swapping the bit : %x\n", swapped_result);
    
    return 0;
}