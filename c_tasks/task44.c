/**
 * @file      : task44.c
 * @brief     : Safe register bit manipulation utility suite.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task44.c -o task44
 */

#include <stdio.h>
#include <stdlib.h>

void clear_buffer(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

int setBit(int n) {
    int bit;
    printf("Enter bit position to set (0-31): ");
    if (scanf("%d", &bit) != 1 || bit < 0 || bit > 31) {
        printf("Invalid bit position calculation dropped.\n");
        clear_buffer();
        return n;
    }
    return (1 << bit) | n;
}

int resetBit(int n) {
    int bit;
    printf("Enter bit position to reset (0-31): ");
    if (scanf("%d", &bit) != 1 || bit < 0 || bit > 31) {
        printf("Invalid bit position calculation dropped.\n");
        clear_buffer();
        return n;
    }
    return (~(1 << bit)) & n;
}

void readBit(int n) {
    int bit;
    printf("Enter target position to read (0-31): ");
    if (scanf("%d", &bit) != 1 || bit < 0 || bit > 31) {
        printf("Invalid position calculation context.\n");
        clear_buffer();
        return;
    }
    int res = (n >> bit) & 1;
    printf("The bit state value is: %d\n", res);
}

int main(void) {
    int n = 0, choice = 0;
    printf("Enter the starting evaluation integer value: ");
    if (scanf("%d", &n) != 1) return EXIT_FAILURE;
    
    while (1) {
        printf("\n--- Bit Operations Management ---\n1. Set Bit\n2. Reset Bit\n3. Read Bit\n4. Exit\nEnter Choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_buffer();
            continue;
        }
        if (choice == 4) break;
        switch(choice) {
            case 1: n = setBit(n); printf("Current register hex layout state: 0x%X\n", n); break;
            case 2: n = resetBit(n); printf("Current register hex layout state: 0x%X\n", n); break;
            case 3: readBit(n); break;
            default: printf("Selection outside bounds matrix mapping rules.\n");
        }
    }
    return EXIT_SUCCESS;
}