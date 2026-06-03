/**
  * @file      : metertofeet.c
  * @brief     : Provides preprocessor macro conversions from meters to feet 
  * utilizing strict operator isolation and type-safe data structures.
  */

#include <stdio.h>

/**
 * @brief Conversion constant matching 1 meter to feet.
 */
#define METERS_TO_FEET_FACTOR 3.28084f

/**
 * @brief Macro function to safely convert meters into feet.
 * @note  Encloses both the parameter and the overall expression in parentheses
 * to safeguard operator precedence in complex mathematical statements.
 */
#define METERS_TO_FEET(meters) ((meters) * METERS_TO_FEET_FACTOR)

int main(void)
{
    float input_meters = 0.0f;
    float converted_feet = 0.0f;
    
    printf("Enter the distance in meters to convert: ");
    
    /* Defensive Input Check: Validates that data matches expected numeric type */
    if (scanf("%f", &input_meters) != 1)
    {
        printf("\nError: Invalid numeric input format encountered.\n");
        return 1;
    }
    
    /* Constraint Validation: Rejects logical anomalies like negative lengths */
    if (input_meters < 0.0f)
    {
        printf("\nError: Physical distance measurements cannot be negative.\n");
        return 1;
    }
    
    /* Perform macro transformation invocation */
    converted_feet = METERS_TO_FEET(input_meters);
    
    printf("\n%.2f meters is equal to %.2f feet\n", input_meters, converted_feet);

    return 0;
}