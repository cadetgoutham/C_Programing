/**
  * @file      : filepointer_capitalize.c
  * @brief     : Creates a dynamic 2D array of strings. Memory for each row is
  * allocated dynamically based on the exact length of each valid
  * input string. Includes string validation for alphabetic characters.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 50

/**
 * @brief  Validates whether a string contains only alphabetic characters and spaces.
 * @param  input_str: Pointer to the null-terminated string to validate.
 * @retval 1 if valid, 0 if an invalid character is found.
 */
int validate_string(const char *input_str)
{
    size_t str_len = strlen(input_str);
    
    for (size_t i = 0; i < str_len; i++)
    {
        char current_char = input_str[i];
        
        // Check if the character is an uppercase letter, lowercase letter, or space
        if (!((current_char >= 'A' && current_char <= 'Z') || 
              (current_char >= 'a' && current_char <= 'z') || 
              (current_char == ' ')))
        {
            return 0; // Invalid string detected
        }
    }
    return 1; // String is valid
}

int main(void)
{
    char input_buffer[MAX_BUFFER_SIZE];
    char **string_matrix = NULL;
    int total_strings = 0;
    int scan_status = 0;
    
    printf("enter number of inputs - ");
    scan_status = scanf(" %d", &total_strings);
    
    // Check if the number of strings was read successfully and is a positive number
    if (scan_status == 1 && total_strings > 0)
    {
        // Allocate an array of pointers (rows of the matrix)
        string_matrix = (char **)malloc(total_strings * sizeof(char *));
        if (string_matrix == NULL)
        {
            printf("\nMemory allocation failed for string matrix structure.\n");
            return 1;
        }
        
        for (int row_index = 0; row_index < total_strings; )
        {
            printf("enter the string - ");
            // Read string including spaces until a newline is reached
            scanf(" %[^\n]", input_buffer);
            
            if (validate_string(input_buffer))
            {
                int string_length = (int)strlen(input_buffer);
                
                // Dynamically allocate memory for the string (+1 byte for the null terminator)
                string_matrix[row_index] = (char *)malloc((string_length + 1) * sizeof(char));
                if (string_matrix[row_index] == NULL)
                {
                    printf("\nMemory allocation failed for row %d.\n", row_index);
                    return 1;
                }
                
                // Copy characters from the input buffer to the dynamic 2D array
                int char_index;
                for (char_index = 0; char_index < string_length; char_index++)
                {
                    string_matrix[row_index][char_index] = input_buffer[char_index];
                }
                // Append the null-terminating character
                string_matrix[row_index][char_index] = '\0';
                
                row_index++; // Move to the next string slot
            }
            else
            {
                printf("\nplease enter valid string...\n");
            }
        }
    }
    else
    {
        printf("\nplease enter valid integer...\n");
        return 1;
    }
    
    printf("\n--- Stored Strings ---\n");
    for (int row_index = 0; row_index < total_strings; row_index++)
    {
        printf("%s\n", string_matrix[row_index]);
    }
    
    // Memory Clean-up (Freeing heap elements)
    for (int row_index = 0; row_index < total_strings; row_index++)
    {
        free(string_matrix[row_index]);
    }
    free(string_matrix);
    
    return 0;
}