/**
 * @file      : task15.c
 * @brief     : Performs a linear search on a dynamically allocated integer array.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task15.c -o task15
 */

#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int search(int size, const int *a, int target)
{
    for (int ind = 0; ind < size; ind++)
    {
        if (a[ind] == target)
            return 1;
    }
    return 0;
}

int main(void)
{
    int size;
    int target;
    
    printf("Enter the size of array: ");
    if (scanf("%d", &size) != 1 || size <= 0)
    {
        printf("Invalid size selection.\n");
        return EXIT_FAILURE;
    }
    
    int *array = (int *)calloc(size, sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failure.\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %d elements of the array:\n", size);
    for (int ind = 0; ind < size; ind++)
    {
        while (scanf("%d", &array[ind]) != 1) {
            printf("Invalid integer format. Re-enter element [%d]: ", ind);
            clear_input_buffer();
        }
    }
    
    printf("Enter element to be searched: ");
    while (scanf("%d", &target) != 1) {
        printf("Invalid target format. Re-enter integer: ");
        clear_input_buffer();
    }
    
    if (search(size, array, target))
    {
        printf("%d is present in array\n", target);
    }
    else
    {
        printf("%d is not present in array\n", target);
    }
    
    free(array);
    return EXIT_SUCCESS;
}