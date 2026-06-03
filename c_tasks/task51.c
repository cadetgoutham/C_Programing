/**
  * @file      : filepointer.c
  * @brief     : Manages a text-based flat-file database containing employee 
  * records (Name, Gender, Location) per line. Supports full 
  * CRUD operations: Create (Add), Read (Display), Update (Modify), 
  * and Delete records.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_FIELD_SIZE  50
#define TEMP_FILE_NAME  "replace.txt"

/**
 * @brief  Displays all employee records currently saved in the file.
 * @param  db_file_path: The filesystem path to the target database text file.
 */
void display_records(const char *db_file_path)
{
    FILE *file_ptr = fopen(db_file_path, "r");
    char row_buffer[MAX_BUFFER_SIZE];
    int line_number = 1;
    
    if (file_ptr == NULL)
    {
        printf("\nSpecified file is not present. Please add a record to create it...\n");
        return;
    }
    
    printf("\n--- Current Employee Records ---\n");
    while (fgets(row_buffer, sizeof(row_buffer), file_ptr) != NULL)
    {
        printf("%d. %s", line_number, row_buffer);
        line_number++;
    }
    
    fclose(file_ptr);
}

/**
 * @brief  Deletes an employee record at a user-specified line number.
 * @param  db_file_path: The original target database text file.
 * @param  temp_file_path: The temporary staging file used during copying.
 */
void delete_record(const char *db_file_path, const char *temp_file_path)
{
    FILE *source_file = fopen(db_file_path, "r");
    FILE *temp_file = fopen(temp_file_path, "w");
    char row_buffer[MAX_BUFFER_SIZE];
    int target_line = 0;
    int current_line = 0;
    
    if (source_file == NULL)
    {
        printf("\nError: Cannot open source file for deletion.\n");
        if (temp_file) fclose(temp_file);
        return;
    }
    if (temp_file == NULL)
    {
        printf("\nError: Cannot create temporary staging file.\n");
        fclose(source_file);
        return;
    }
    
    printf("Please enter the line number you want to delete: ");
    if (scanf("%d", &target_line) != 1 || target_line <= 0)
    {
        printf("Invalid line number entered.\n");
        fclose(source_file);
        fclose(temp_file);
        return;
    }
    
    // Read line-by-line instead of character-by-character to avoid stream corruption
    while (fgets(row_buffer, sizeof(row_buffer), source_file) != NULL)
    {
        current_line++;
        
        // Skip writing the target line to the temporary file to execute the deletion
        if (current_line != target_line)
        {
            fputs(row_buffer, temp_file);
        }
    }
    
    fclose(source_file);
    fclose(temp_file);
    
    // Replace old file with the newly generated temporary file
    remove(db_file_path);
    rename(temp_file_path, db_file_path);
    
    if (target_line <= current_line)
    {
        printf("Line %d successfully deleted.\n", target_line);
    }
    else
    {
        printf("Warning: Target line exceeded total available lines (%d). No records removed.\n", current_line);
    }
}

/**
 * @brief  Modifies an existing employee record at a user-specified line number.
 * @param  db_file_path: The original target database text file.
 * @param  temp_file_path: The temporary staging file used during copying.
 */
void modify_record(const char *db_file_path, const char *temp_file_path)
{
    FILE *source_file = fopen(db_file_path, "r");
    FILE *temp_file = fopen(temp_file_path, "w");
    char new_record_string[MAX_BUFFER_SIZE];
    char emp_name[MAX_FIELD_SIZE];
    char emp_gender[MAX_FIELD_SIZE];
    char emp_location[MAX_FIELD_SIZE];
    char row_buffer[MAX_BUFFER_SIZE];
    int target_line = 0;
    int current_line = 0;
    
    if (source_file == NULL)
    {
        printf("\nError: Source file does not exist. Add records first.\n");
        if (temp_file) fclose(temp_file);
        return;
    }
    if (temp_file == NULL)
    {
        printf("\nError: Cannot create temporary staging file.\n");
        fclose(source_file);
        return;
    }
    
    printf("\nEnter line number to replace: ");
    if (scanf("%d", &target_line) != 1 || target_line <= 0)
    {
        printf("Invalid line number.\n");
        fclose(source_file);
        fclose(temp_file);
        return;
    }
    
    // Securely ingest field metrics without leaving dangling newline anomalies inside stdin
    printf("enter the name of employee - ");
    scanf(" %[^\n]", emp_name);
    
    printf("enter the gender of employee - ");
    scanf(" %[^\n]", emp_gender);
    
    printf("enter the location of employee - ");
    scanf(" %[^\n]", emp_location);
    
    // Safely format separate metadata fields into a structured comma-separated record row
    sprintf(new_record_string, "%s, %s, %s\n", emp_name, emp_gender, emp_location);
    
    while (fgets(row_buffer, sizeof(row_buffer), source_file) != NULL)
    {
        current_line++;
        
        if (current_line == target_line)
        {
            fputs(new_record_string, temp_file);
        }
        else
        {
            fputs(row_buffer, temp_file);
        }
    }
    
    fclose(source_file);
    fclose(temp_file);
    
    remove(db_file_path);
    rename(temp_file_path, db_file_path);
    
    if (target_line <= current_line)
    {
        printf("Successfully replaced line %d with: %s", target_line, new_record_string);
    }
    else
    {
        printf("Warning: Target line was out of range. Modification aborted.\n");
    }
}

/**
 * @brief  Appends a newly registered employee block to the base of the file stream.
 * @param  db_file_path: The filesystem path to the target database text file.
 */
void add_record(const char *db_file_path)
{
    char emp_name[MAX_FIELD_SIZE];
    char emp_gender[MAX_FIELD_SIZE];
    char emp_location[MAX_FIELD_SIZE];
    char combined_record_string[MAX_BUFFER_SIZE];
    
    FILE *file_ptr = fopen(db_file_path, "a");
    if (file_ptr == NULL)
    {
        printf("Error: Could not open file for appending.\n");
        return;
    }
    
    printf("enter the name of employee - ");
    scanf(" %[^\n]", emp_name);
    
    printf("enter the gender of employee - ");
    scanf(" %[^\n]", emp_gender);
    
    printf("enter the location of employee - ");
    scanf(" %[^\n]", emp_location);
    
    sprintf(combined_record_string, "%s, %s, %s\n", emp_name, emp_gender, emp_location);
    
    fputs(combined_record_string, file_ptr);
    fclose(file_ptr);
    
    printf("Record added successfully.\n");
}

int main(void)
{
    char database_path[256];
    char user_menu_choice;
    int terminate_signal = 0;
    
    printf("Enter path of source file: ");
    if (scanf("%255s", database_path) != 1)
    {
        printf("Invalid path input.\n");
        return 1;
    }
    
    while (!terminate_signal)
    {
        printf("\n--- Employee Management Menu ---\n");
        printf("a. ADD\n");
        printf("b. REPLACE/MODIFY\n");
        printf("c. DELETE\n");
        printf("d. DISPLAY\n");
        printf("e. EXIT\n");
        printf("enter your choice - ");
        scanf(" %c", &user_menu_choice);
        
        switch (user_menu_choice)
        {
            case 'a':
                add_record(database_path);
                break;
                
            case 'b':
                modify_record(database_path, TEMP_FILE_NAME);
                break;
                
            case 'c':
                delete_record(database_path, TEMP_FILE_NAME);
                break;
                
            case 'd':
                display_records(database_path);
                break;
                
            case 'e':
                terminate_signal = 1;
                break;
                
            default:
                printf("\nPlease enter a valid menu option.\n");
                break;
        }
    }
    
    printf("\nSuccessfully updated list and exited program safely.\n");
    return 0;
}