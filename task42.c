/**
 * @file      : task42.c
 * @brief     : Routes arithmetic operations via a clean lookup array of function pointers.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task42.c -o task42
 * Usage: ./task42 <num1> <num2> <operator>
 */

#include <stdio.h>
#include <stdlib.h>

int add(int num1, int num2)  { return num1 + num2; }
int sub(int num1, int num2)  { return num1 - num2; }
int mul(int num1, int num2)  { return num1 * num2; }
int divi(int num1, int num2) { return (num2 != 0) ? (num1 / num2) : 0; }
int mod(int num1, int num2)  { return (num2 != 0) ? (num1 % num2) : 0; }
int bit(int num1, int num2)  { return num1 ^ num2; }

int main(int argc, char *argv[])
{
    if (argc < 4) {
        printf("Usage: %s <num1> <num2> <operator>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *end1, *end2;
    int num1 = (int)strtol(argv[1], &end1, 10);
    int num2 = (int)strtol(argv[2], &end2, 10);
    char op = argv[3][0];
    
    if (*end1 != '\0' || *end2 != '\0') {
        printf("Error: Argument parsing error.\n");
        return EXIT_FAILURE;
    }

    char op_tokens[] = {'+', '-', '*', '/', '%', '^'};
    int (*func_ptr[])(int, int) = {add, sub, mul, divi, mod, bit};
    int target_idx = -1;
    
    for (int i = 0; i < 6; i++) {
        if (op_tokens[i] == op) {
            target_idx = i;
            break;
        }
    }
    
    if (target_idx == -1) {
        printf("Error: Invalid operation token requested.\n");
        return EXIT_FAILURE;
    }
    
    if ((op == '/' || op == '%') && num2 == 0) {
        printf("Error: Zero denominators are invalid.\n");
        return EXIT_FAILURE;
    }
    
    int result = func_ptr[target_idx](num1, num2);
    printf("Result execution response: %d\n", result);
    
    return EXIT_SUCCESS;
}