/**
  * @file      : structure_filepointer.c
  * @brief     : Manages a fixed-width employee database utilizing C structure 
  * serialization in binary mode ("rb", "wb", "ab"). Supports adding, 
  * modifying, deleting, and displaying raw block records.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_BUFFER_SIZE   1024
#define NAME_FIELD_LEN     20
#define GENDER_FIELD_LEN   10
#define LOCATION_FIELD_LEN 20
#define TEMP_FILE_NAME     "replace.bin" // Using .bin extension since data is binary

typedef struct emp_details
{
    char name[NAME_FIELD_LEN];
    char gender[GENDER_FIELD_LEN];
    unsigned short int code;
    unsigned int age;
    char location[LOCATION_FIELD_LEN];
} EmployeeRecord;

/**
 * @brief  Displays all serialized structural records stored inside the binary file.
 * @param  db_path: Target filesystem destination string.
 */
void display_records(const char db_path[])
{
    FILE *file_ptr = fopen(db_path, "rb");
    int record_counter = 1;
    EmployeeRecord current_employee;
    
    if (file_ptr == NULL)
    {
        printf("\nSpecified file is not present. Please create a record first...\n");
        return;
    }
    
    // Read sequentially exactly 1 block of the size of EmployeeRecord from the binary stream
    while (fread(&current_employee, sizeof(EmployeeRecord), 1, file_ptr) == 1)
    {
        printf("\n%d. Employee Name : %s", record_counter, current_employee.name);
        printf("\n   Gender        : %s", current_employee.gender);
        printf("\n   Emp Code      : %hu", current_employee.code);
        printf("\n   Age           : %u", current_employee.age);
        printf("\n   Location      : %s\n", current_employee.location);
        record_counter++;
    }

    fclose(file_ptr);
}

/**
 * @brief  Appends a single serialized structural block onto the end of the binary stream.
 * @param  db_path: Target database destination.
 */
void add_record(const char db_path[])
{
    FILE *file_ptr = NULL;
    EmployeeRecord new_employee;
    
    // Initialize structure memory blocks to 0 to prevent garbage stack bytes from polluting file
    memset(&new_employee, 0, sizeof(EmployeeRecord));
    
    // Defensive width-limiting on user strings protects the binary structure from breaking or corrupting offsets
    printf("enter name (max %d chars) - ", NAME_FIELD_LEN - 1);
    scanf(" %19[^\n]", new_employee.name);
    
    printf("enter gender (max %d chars) - ", GENDER_FIELD_LEN - 1);
    scanf(" %9s", new_employee.gender);
    
    printf("enter code - ");
    scanf(" %hu", &new_employee.code);
    
    printf("enter age - ");
    scanf(" %u", &new_employee.age);
    
    printf("enter location (max %d chars) - ", LOCATION_FIELD_LEN - 1);
    scanf(" %19[^\n]", new_employee.location);
    
    file_ptr = fopen(db_path, "ab");
    if (file_ptr == NULL)
    {
        printf("\nError: Could not open file to append data.\n");
        return;
    }
    
    // Check if 1 element was successfully processed to verify write operations
    if (fwrite(&new_employee, sizeof(EmployeeRecord), 1, file_ptr) == 1)
    {
        printf("\nContents written to binary file successfully!\n");
    }
    else
    {
        printf("\nError writing data to file!\n");
    }

    fclose(file_ptr);
}

/**
 * @brief  Modifies an existing structure entry at a specified index sequence.
 * @param  db_path: Path to target file.
 * @param  temp_path: Secondary swap pipeline destination.
 */
void modify_record(const char db_path[], const char temp_path[])
{
    FILE *source_file_ptr = NULL;
    FILE *temp_file_ptr = NULL;
    EmployeeRecord operational_buffer;
    EmployeeRecord modification_buffer;
    int target_record_index;
    int current_record_position = 0;
    
    source_file_ptr = fopen(db_path, "rb");
    if (source_file_ptr == NULL)
    {
        printf("\nError: Source file does not exist. Add records first.\n");
        return;
    }
    
    printf("\nEnter structural record index number to replace: ");
    if (scanf("%d", &target_record_index) != 1 || target_record_index <= 0)
    {
        printf("Invalid choice integer evaluated.\n");
        fclose(source_file_ptr);
        return;
    }

    memset(&modification_buffer, 0, sizeof(EmployeeRecord));
    
    printf("enter new name - ");
    scanf(" %19[^\n]", modification_buffer.name);
    
    printf("enter new gender - ");
    scanf(" %9s", modification_buffer.gender);
    
    printf("enter new code - ");
    scanf(" %hu", &modification_buffer.code);
    
    printf("enter new age - ");
    scanf(" %u", &modification_buffer.age);
    
    printf("enter new location - ");
    scanf(" %19[^\n]", modification_buffer.location);
    
    temp_file_ptr = fopen(temp_path, "wb");
    if (temp_file_ptr == NULL)
    {
        printf("\nError compiling staging workspace environment.\n");
        fclose(source_file_ptr);
        return;
    }
    
    // Read matching sized chunks blocks from the file stream sequentially
    while (fread(&operational_buffer, sizeof(EmployeeRecord), 1, source_file_ptr) == 1)
    {
        current_record_position++;
        
        if (current_record_position == target_record_index)
        {
            fwrite(&modification_buffer, sizeof(EmployeeRecord), 1, temp_file_ptr);
        }
        else
        {
            fwrite(&operational_buffer, sizeof(EmployeeRecord), 1, temp_file_ptr);
        }
    }
    
    fclose(temp_file_ptr);
    fclose(source_file_ptr);
    
    remove(db_path);
    rename(temp_path, db_path);
    
    if (target_record_index <= current_record_position)
    {
        printf("\nSuccessfully replaced record index number '%d'.\n", target_record_index);
    }
    else
    {
        printf("\nWarning: Provided structural index out of file storage bound constraints.\n");
    }
}

/**
 * @brief  Omits an existing structure entry out of the stream by structural index filtering.
 * @param  db_path: Path to target file.
 * @param  temp_path: Secondary swap pipeline destination.
 */
void delete_record(const char db_path[], const char temp_path[])
{
    FILE *source_file_ptr = NULL;
    FILE *temp_file_ptr = NULL;
    EmployeeRecord operational_buffer;
    int target_record_index;
    int current_record_position = 1;
    
    source_file_ptr = fopen(db_path, "rb");
    if (source_file_ptr == NULL)
    {
        printf("\nSpecified database target is not present.\n");
        return;
    }
    
    printf("\nPlease enter the record index number you want to delete : ");
    if (scanf("%d", &target_record_index) != 1 || target_record_index <= 0)
    {
        printf("Invalid parameter format.\n");
        fclose(source_file_ptr);
        return;
    }
    
    temp_file_ptr = fopen(temp_path, "wb");
    if (temp_file_ptr == NULL)
    {
        printf("\nError processing target environment storage swap blocks.\n");
        fclose(source_file_ptr);
        return;
    }
    
    while (fread(&operational_buffer, sizeof(EmployeeRecord), 1, source_file_ptr) == 1)
    {
        // Write back everything to temporary file EXCEPT the block index slated for removal
        if (target_record_index != current_record_position)
        {
            fwrite(&operational_buffer, sizeof(EmployeeRecord), 1, temp_file_ptr);
        }
        current_record_position++;
    }
    
    fclose(source_file_ptr);
    fclose(temp_file_ptr);
    
    remove(db_path);
    rename(temp_path, db_path);
    
    printf("\nSuccessfully processed data synchronization loop for index %d...\n", target_record_index);
}

int main(void)
{
    char system_db_path[PATH_BUFFER_SIZE];
    char user_menu_selection;
    int execution_status = 0;
    
    printf("enter path name - ");
    // Restricting raw path scanning to prevent stack vulnerabilities
    if (scanf(" %1023s", system_db_path) != 1)
    {
        return 1;
    }
    
    while (execution_status == 0)
    {
        printf("\n--- Binary DB Management Dashboard ---");
        printf("\na. ADD RECORD");
        printf("\nb. MODIFY RECORD");
        printf("\nc. DELETE RECORD");
        printf("\nd. DISPLAY RECORDS");
        printf("\ne. EXIT");
        printf("\nenter your choice - ");
        scanf(" %c", &user_menu_selection);
        
        switch (user_menu_selection)
        {
            case 'a':
                add_record(system_db_path);
                break;
                
            case 'b':
                modify_record(system_db_path, TEMP_FILE_NAME);
                break;
                
            case 'c':
                delete_record(system_db_path, TEMP_FILE_NAME);
                break;
                
            case 'd':
                display_records(system_db_path);
                break;
                
            case 'e':
                execution_status = 1;
                break;
                
            default:
                printf("\nPlease enter a valid alphanumeric option menu flag.\n");
                break;
        }
    }
    
    printf("\nSuccessfully closed structures streams database interface safely.\n");
    return 0;
}