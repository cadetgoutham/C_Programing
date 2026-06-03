/**
  * @file      : email_hashing.c
  * @brief     : Implements a flat-key hash table utilizing linear probing open 
  * addressing collision resolution strategies to organize and manage 
  * validated string email entries.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_TABLE_SIZE  64  
#define MAX_EMAIL_LEN    50

// Declaring global array of pointers to hold email strings
char *email_hash_table[HASH_TABLE_SIZE]; 

// Function Declarations
int is_valid_email(const char *email);
void insert_email(void);
void print_hash_table(void);
void delete_email(void);
void search_email(void);

int main(void)
{
    int user_choice;
    int run_program = 1;
    
    // Explicitly initialize the hash table array elements to NULL
    memset(email_hash_table, 0, sizeof(email_hash_table));
    
    // Replaced dangerous recursive function chains with a secure loop control block
    while (run_program)
    {
        printf("\n--- Email Management Hash Table ---\n");
        printf("1. Insert Email\n2. Print Table\n3. Delete Email\n4. Search Email\n5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &user_choice) != 1)
        {
            printf("Invalid input format.\n");
            // Clear input stream to prevent infinite scanning loops
            while (getchar() != '\n');
            continue;
        }
        
        switch (user_choice)
        {
            case 1:
                insert_email();
                break;
                
            case 2:
                print_hash_table();
                break;
                
            case 3:
                delete_email();
                break;
                
            case 4:
                search_email();
                break;
                
            case 5:
                run_program = 0;
                break;
                
            default:
                printf("\nPlease enter a valid option.\n");
                break;
        }
    }
    
    // Memory Clean-up: Free all dynamically allocated elements before terminating
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (email_hash_table[i] != NULL)
        {
            free(email_hash_table[i]);
            email_hash_table[i] = NULL;
        }
    }
    
    printf("\nProgram terminated successfully.\n");
    return 0;
}

/**
 * @brief  Validates whether a string matches basic numeric and character boundaries.
 * @param  email: Pointer to the target string evaluated.
 * @return 1 if structural match succeeds, 0 if validation fails.
 */
int is_valid_email(const char *email)
{
    if (email == NULL || *email == '\0')
    {
        return 0;
    }

    size_t email_length = strlen(email);
    size_t valid_char_count = 0;
    int total_dots = 0;
    int total_ats = 0;

    for (size_t i = 0; i < email_length; i++)
    {
        unsigned char ch = (unsigned char)email[i];
        
        // Use standard C library char validation functions instead of magic ASCII integers
        if (isalnum(ch)) 
        {
            valid_char_count++;
        }
        else if (ch == '.')
        {
            total_dots++;
            valid_char_count++;
        }
        else if (ch == '@')
        {
            total_ats++;
            valid_char_count++;
        }
    }
    
    // Returns 1 if all characters are valid, there is exactly one '@', and no more than 2 dots
    if (valid_char_count == email_length && total_dots <= 2 && total_ats == 1) 
    {
        return 1; 
    }
    
    return 0;
}

/**
 * @brief  Calculates a simple division-method index key and pushes a copy of 
 * the string into the hash table using open-addressing linear probing.
 */
void insert_email(void)
{
    char input_buffer[MAX_EMAIL_LEN];
    int calculated_hash_key = 0;
    int total_ascii_sum = 0;
    
    printf("Enter the email to insert: ");
    scanf(" %49s", input_buffer);
    
    if (is_valid_email(input_buffer) == 1)
    {
        size_t string_len = strlen(input_buffer);
        for (size_t i = 0; i < string_len; i++)
        {
            total_ascii_sum += (unsigned char)input_buffer[i];
        }
        
        // Base compression key generation
        calculated_hash_key = total_ascii_sum % 10;
        int target_slot = calculated_hash_key;
        int elements_inspected = 0;

        // Linear Probing logic to resolve array collisions safely
        while (email_hash_table[target_slot] != NULL)
        {
            // If the email is already in the hash table, avoid adding a duplicate
            if (strcmp(email_hash_table[target_slot], input_buffer) == 0)
            {
                printf("Email already exists in the records at index %d.\n", target_slot);
                return;
            }

            // Move to the next index sequentially, wrapping around using a modulo operator
            target_slot = (target_slot + 1) % HASH_TABLE_SIZE;
            elements_inspected++;

            // Hash table full guard check
            if (elements_inspected == HASH_TABLE_SIZE)
            {
                printf("\nError: Hash table storage is full!\n");
                return;
            }
        }
        
        /* Fixed memory corruption bug: Allocate persistent memory on the heap 
         * instead of pointing to a temporary, recycling local stack pointer frame. */
        email_hash_table[target_slot] = strdup(input_buffer);
        if (email_hash_table[target_slot] == NULL)
        {
            printf("System Error: Memory allocation failure.\n");
            return;
        }
        
        printf("Email successfully inserted at index: %d\n", target_slot);
    }
    else
    {
        printf("\nError: Invalid email structure formatting rule match failed.\n");
    }
}

/**
 * @brief  Displays a map layout of all current contents inside the pointer array.
 */
void print_hash_table(void)
{
    printf("\nIndex\tStored Email Pointer Metadata\n");
    printf("------------------------------------\n");
    
    // Corrected off-by-one error (changed loop boundary from <= to < size)
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (email_hash_table[i] != NULL)
        {
            printf("%d\t%s\n", i, email_hash_table[i]);
        }
        else
        {
            printf("%d\t[EMPTY]\n", i);
        }
    }
}

/**
 * @brief  Finds and deletes a targeted string match out of the global hash table array.
 */
void delete_email(void)
{
    char target_email[MAX_EMAIL_LEN];
    int was_found = 0;
    
    printf("Enter the mail to be deleted: ");
    scanf(" %49s", target_email);
    
    if (is_valid_email(target_email) == 1)
    {
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            if (email_hash_table[i] != NULL)
            {
                if (strcmp(target_email, email_hash_table[i]) == 0) 
                {
                    // Clean memory dynamically before clearing the pointer track address
                    free(email_hash_table[i]);
                    email_hash_table[i] = NULL;
                    
                    printf("Email successfully deleted from index %d.\n", i);
                    was_found = 1;
                    break;
                }   
            }
        }
        
        if (!was_found)
        {
            printf("Specified email was not found in the table records.\n");
        }
    }
    else
    {
        printf("\nError: Invalid email string input pattern rules.\n");
    }   
}

/**
 * @brief  Searches for a targeted email string sequentially through active hash partitions.
 */
void search_email(void)
{
    char search_target[MAX_EMAIL_LEN];
    int was_found = 0;
    
    printf("Enter the mail to be searched: ");
    scanf(" %49s", search_target);
    
    if (is_valid_email(search_target) == 1)
    {
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            if (email_hash_table[i] != NULL)
            {
                if (strcmp(search_target, email_hash_table[i]) == 0)
                {
                    printf("Email found! Stored at table index position: %d\n", i);
                    was_found = 1;
                    break;
                }
            }
        }
        
        if (!was_found)
        {
            printf("Given email is not found in the hash table records.\n");
        }
    }
    else
    {
        printf("Error: Invalid email formatting syntax entry rejected.\n");
    }
}