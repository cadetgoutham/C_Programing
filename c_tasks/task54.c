/**
  * @file      : input_checking.c
  * @brief     : Accepts an employee record via command-line arguments,
  * validates the formatted fields defensively, displays them, 
  * and appends the synchronized payload safely to a text database.
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define REQUIRED_ARGS 5
#define PREFIX_LEN    4
#define CODE_LEN      8

/**
 * @brief Validates if a string contains only alphabetic characters and spaces.
 * @param str Null-terminated string to validate.
 * @return int Returns 1 if valid, 0 otherwise.
 */
int string_validation(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return 0;
    }

    for (size_t loop_index = 0; str[loop_index] != '\0'; loop_index++)
    {
        unsigned char ch = (unsigned char)str[loop_index];
        if (!isalpha(ch) && ch != ' ')
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Validates if a string contains only digits (useful for numeric fields like age).
 * @param str Null-terminated string to validate.
 * @return int Returns 1 if valid, 0 otherwise.
 */
int numeric_validation(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return 0;
    }

    for (size_t loop_index = 0; str[loop_index] != '\0'; loop_index++)
    {
        if (!isdigit((unsigned char)str[loop_index]))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Validates if the employee code is exactly 8 characters long 
 * and strictly starts with "VVDN" or "vvdn".
 * @param str Null-terminated string to validate.
 * @return int Returns 1 if valid, 0 otherwise.
 */
int code_validation(const char *str)
{
    if (str == NULL || strlen(str) != CODE_LEN)
    {
        return 0;
    }

    /* Verify the prefix matching without overflowing local temporary windows */
    if (strncmp(str, "VVDN", PREFIX_LEN) == 0 || strncmp(str, "vvdn", PREFIX_LEN) == 0)
    {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /* 1. Defensive Argument Guard: Rejects execution if inputs are missing */
    if (argc < REQUIRED_ARGS)
    {
        printf("Error: Missing parameters.\n");
        printf("Usage: %s <Name> <EmpCode> <Age> <Location>\n", argv[0]);
        return 1;
    }

    const char *emp_name     = argv[1];
    const char *emp_code     = argv[2];
    const char *emp_age      = argv[3];
    const char *emp_location = argv[4];

    /* 2. Form Input Sanitization Strategy */
    if (!string_validation(emp_name))
    {
        printf("Validation Error: Employee Name must contain only letters and spaces.\n");
        return 1;
    }

    if (!code_validation(emp_code))
    {
        printf("Validation Error: Employee Code must be exactly 8 characters long and begin with 'VVDN' or 'vvdn'.\n");
        return 1;
    }

    if (!numeric_validation(emp_age))
    {
        printf("Validation Error: Employee Age must be a positive integer.\n");
        return 1;
    }

    if (!string_validation(emp_location))
    {
        printf("Validation Error: Employee Location must contain only letters and spaces.\n");
        return 1;
    }

    /* 3. Output payload presentation to the user */
    printf("\n--- Processing Employee Record ---\n");
    printf("Name     : %s\n", emp_name);
    printf("Code     : %s\n", emp_code);
    printf("Age      : %s\n", emp_age);
    printf("Location : %s\n", emp_location);

    /* 4. Secure File Append Operation */
    FILE *fp = fopen("Record.txt", "a");
    if (fp == NULL)
    {
        printf("System Error: Unable to open database storage engine file.\n");
        return 1;
    }

    fprintf(fp, "emp name : %s\nemp code : %s\nemp age : %s\nemp location :%s\n\n", 
            emp_name, emp_code, emp_age, emp_location);
    
    fclose(fp);

    printf("\nSuccessfully inserted record into database file.\n");
    return 0;
}