/**
 * @file      : task41.c
 * @brief     : Executes standard arithmetic evaluations using targeted function pointers.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task41.c -o task41
 * Usage: ./task41 <num1> <num2> <operator>
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
        printf("Error: Missing parameters.\nUsage: %s <num1> <num2> <operator>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    char *endptr2;
    long num1 = strtol(argv[1], &endptr1, 10);
    long num2 = strtol(argv[2], &endptr2, 10);
    char operator = argv[3][0];
    int result = 0;
    
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        printf("Error: Invalid integer input values.\n");
        return EXIT_FAILURE;
    }
    
    int (*op_ptr)(int, int) = NULL;
    
    switch (operator) {
        case '+': op_ptr = add;  break;
        case '-': op_ptr = sub;  break;
        case '*': op_ptr = mul;  break;
        case '/': op_ptr = divi; break;
        case '%': op_ptr = mod;  break;
        case '^': op_ptr = bit;  break;
        default:
            printf("Error: Unsupported operator configuration context '%c'.\n", operator);
            return EXIT_FAILURE;
    }
    
    if ((operator == '/' || operator == '%') && num2 == 0) {
        printf("Error: Division by zero is prohibited.\n");
        return EXIT_FAILURE;
    }
    
    result = op_ptr((int)num1, (int)num2);
    printf("Result execution response: %d\n", result);
    
    return EXIT_SUCCESS;
}