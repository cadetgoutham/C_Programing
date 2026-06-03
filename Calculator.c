/**
 * @file      : Calculator.c
 * @brief     : Industry-standard, crash-safe interactive calculator supporting 
 * basic arithmetic, multi-element tracking, moduli, powers, and factorials.
 * @note      : Compiles cleanly with standard C flags: gcc -Wall -Wextra -std=c11
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Clears remaining garbage characters from standard input stream buffer.
 * Fixes the common bug where text inputs trigger infinite loops in scanf.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addition(void) {
    int count = 0;
    long long total = 0;
    int current_input = 0;

    printf("Enter how many numbers to add: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid element count. Operation canceled.\n");
        clear_input_buffer();
        return;
    }

    printf("Enter %d numbers to add:\n", count);
    for (int temp = 0; temp < count; temp++) {
        while (scanf("%d", &current_input) != 1) {
            printf("Invalid input format. Please supply a valid whole integer: ");
            clear_input_buffer();
        }
        total += current_input;
    }
    printf("\nThe total sum = %lld\n", total);
}

void subtraction(void) {
    int num1, num2;

    printf("\nPlease enter first number  : ");
    if (scanf("%d", &num1) != 1) { clear_input_buffer(); return; }
    
    printf("Please enter second number : ");
    if (scanf("%d", &num2) != 1) { clear_input_buffer(); return; }

    printf("\n%d - %d = %d\n", num1, num2, num1 - num2);
}

void multiplication(void) {
    int count = 0;
    long long total = 1;
    int current_input = 0;

    printf("Enter number of elements to multiply: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid element count. Operation canceled.\n");
        clear_input_buffer();
        return;
    }

    printf("Enter %d numbers to multiply:\n", count);
    for (int temp = 0; temp < count; temp++) {
        while (scanf("%d", &current_input) != 1) {
            printf("Invalid input format. Please supply a valid whole integer: ");
            clear_input_buffer();
        }
        total *= current_input;
    }
    printf("\nThe total product = %lld\n", total);
}

void division(void) {
    double num1, num2;

    printf("\nPlease enter first number  : ");
    if (scanf("%lf", &num1) != 1) { clear_input_buffer(); return; }
    
    printf("Please enter second number : ");
    if (scanf("%lf", &num2) != 1) { clear_input_buffer(); return; }

    /* CRITICAL: Hardware Fault Guard against dividing by zero */
    if (num2 == 0.0) {
        printf("\nError: Mathematical failure! Division by zero is undefined.\n");
        return;
    }

    /* Enhanced to output fractional floating-point values accurately */
    printf("\n%.2f / %.2f = %.4f\n", num1, num2, num1 / num2);
}

void modulus(void) {
    int num1, num2;

    printf("\nPlease enter first number   : ");
    if (scanf("%d", &num1) != 1) { clear_input_buffer(); return; }
    
    printf("Please enter second number  : ");
    if (scanf("%d", &num2) != 1) { clear_input_buffer(); return; }

    /* CRITICAL: Hardware Fault Guard against modulus by zero */
    if (num2 == 0) {
        printf("\nError: Modulus by zero is undefined.\n");
        return;
    }

    printf("\n%d Modulus %d = %d\n", num1, num2, num1 % num2);
}

void factorial(void) {
    int number = 0;
    unsigned long long fact = 1;

    printf("\nEnter a number to find factorial (0-20): ");
    if (scanf("%d", &number) != 1 || number < 0) {
        printf("Invalid entry. Factorials require positive integers.\n");
        clear_input_buffer();
        return;
    }

    /* CRITICAL: Protect against 64-bit integer overflow bounds limit */
    if (number > 20) {
        printf("Value too large! Calculations above 20! overflow standard 64-bit bounds.\n");
        return;
    }

    for (int temp = 1; temp <= number; temp++) {
        fact *= temp;
    }

    printf("Factorial of %d = %llu\n", number, fact);
}

void power(void) {
    double base;
    int expo;
    double result = 1.0;

    printf("Enter a base number: ");
    if (scanf("%lf", &base) != 1) { clear_input_buffer(); return; }
    
    printf("Enter an exponent: ");
    if (scanf("%d", &expo) != 1) { clear_input_buffer(); return; }

    int positive_expo = (expo < 0) ? -expo : expo;

    for (int i = 0; i < positive_expo; i++) {
        result *= base;
    }

    /* Enhanced to support negative exponents cleanly */
    if (expo < 0) {
        result = 1.0 / result;
    }

    printf("Answer = %.6g\n", result);
}

int main(void) {
    char operation;

    while (true) {
        printf("\nEnter \n"
               "+ for Addition\n"
               "- for Subtraction\n"
               "* for Multiplication\n"
               "/ for Division\n"
               "? for Modulus\n"
               "^ for Power\n"
               "! for Factorial\n"
               "x for exit\n"
               "Selection: ");
               
        /* The leading space inside " %c" tells scanf to discard preceding whitespace/newlines */
        if (scanf(" %c", &operation) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (operation) {
            case '+': addition();       break;
            case '-': subtraction();    break;
            case '*': multiplication();  break;
            case '/': division();       break;
            case '?': modulus();        break;
            case '^': power();          break;
            case '!': factorial();      break;
            case 'x': 
                printf("Exiting application...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("\nError: Unrecognized selection. Choose a valid option.\n");
                clear_input_buffer();
        }
    }
    return 0;
}