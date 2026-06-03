/**
  * @file      : email_id.c
  * @brief     : Processes command-line arguments representing a user's name,
  * normalizes the characters to lowercase, and constructs a standardized
  * corporate email address suffix.
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAIL_BUFFER 100
#define EMAIL_DOMAIN     "@vvdntech.com"

int main(int argc, char *argv[])
{
    char email_address[MAX_EMAIL_BUFFER];
    int write_index = 0;
    
    // 1. Defensive Argument Guard: Verify that at least one name argument is provided
    if (argc < 2)
    {
        printf("Error: Missing parameters.\n");
        printf("Usage: %s <first_name> <last_name_or_initials>\n", argv[0]);
        return 1;
    }
    
    // Clear the destination buffer entirely to ensure safety
    memset(email_address, 0, sizeof(email_address));

    // 2. Process each command-line argument provided by the user
    for (int arg_index = 1; arg_index < argc; arg_index++)
    {
        int char_index = 0;
        
        // Loop through each character of the current string argument until the null-terminator
        while (argv[arg_index][char_index] != '\0')
        {
            /* Safety Guard: Ensure we leave enough room in the buffer for the character,
             * a potential delimiter, and the entire appended email domain string. */
            if (write_index >= (MAX_EMAIL_BUFFER - (int)strlen(EMAIL_DOMAIN) - 2))
            {
                printf("Error: Input arguments exceed maximum safe email buffer length.\n");
                return 1;
            }
            
            // Normalize all uppercase alphabetic characters directly to lowercase
            email_address[write_index] = tolower((unsigned char)argv[arg_index][char_index]);
            
            write_index++;
            char_index++;
        }
        
        // Append a dot separator between individual name arguments (e.g., first.last)
        email_address[write_index] = '.';
        write_index++;
    }
    
    /* 3. Strip the trailing delimiter: Replace the final redundant dot character 
     * placed by the loop with a proper null-terminator string boundary. */
    if (write_index > 0)
    {
        email_address[write_index - 1] = '\0';
    }
    
    // 4. Safely concatenate the company domain suffix to the formatted username
    strcat(email_address, EMAIL_DOMAIN);
    
    printf("OUTPUT : %s\n", email_address);
    
    return 0;
}