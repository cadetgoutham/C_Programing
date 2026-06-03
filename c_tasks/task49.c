/**
  * @file      : filepointer_capitalize.c
  * @brief     : Opens a user-specified text file in read-write mode and 
  * capitalizes the first letter of every word directly in the file.
  */

#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LEN 50

int main(void)
{
    FILE *file_ptr = NULL;
    char current_char;
    char target_file_name[MAX_FILENAME_LEN];
    
    printf("enter the file name you want to open - ");
    // Limit string input reading to prevent buffer overflow vulnerabilities
    scanf("%49s", target_file_name);
    
    // Open the specified file in "r+" mode (Read and Write from the beginning)
    file_ptr = fopen(target_file_name, "r+");
    if (file_ptr == NULL)
    {
        printf("Error: Could not open file '%s'. Make sure it exists.\n", target_file_name);
        return 1;
    }
    
    // Process the absolute first character of the file
    current_char = fgetc(file_ptr);
    if (current_char >= 'a' && current_char <= 'z')
    {
        /* Since fgetc automatically advances the internal stream pointer by 1 byte, 
         * we must back up 1 byte from the CURRENT position (indicated by the final '1' parameter)
         * to overwrite the character we just read. */
        fseek(file_ptr, -1L, SEEK_CUR);
        
        // Overwrite the character with its uppercase variant and save it to the file
        fputc(current_char - 32, file_ptr);
        
        /* Flush or sync the stream state to ensure the file cursor updates properly 
         * after a write operation before a subsequent read occurs. */
        fseek(file_ptr, 0L, SEEK_CUR);
    }
    
    // Iterate through the remainder of the file stream until End-Of-File (EOF)
    while (current_char != EOF)
    {
        // Word boundaries are defined by spaces or newline characters
        if (current_char == ' ' || current_char == '\n')
        {
            current_char = fgetc(file_ptr);
            
            // Check if the beginning character of the newly detected word is lowercase
            if (current_char >= 'a' && current_char <= 'z')
            {
                // Back up the file cursor by 1 byte relative to the current position
                fseek(file_ptr, -1L, SEEK_CUR);
                
                // Write the capitalized character over the original lowercase letter
                fputc(current_char - 32, file_ptr);
                
                // Synchronize positions to resume forward scanning safely
                fseek(file_ptr, 0L, SEEK_CUR);
            }
        }
        else
        {
            // Read the next character sequentially if no word boundary was found
            current_char = fgetc(file_ptr);
        }
    }
    
    // Close the file stream cleanly to write changes to disk and release system resources
    fclose(file_ptr);
    printf("File processing complete. Words capitalized successfully.\n");
    
    return 0;
}