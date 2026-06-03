/**
 * @file      : task14.c
 * @brief     : Analyses stock prices across three markets over 10 days,
 * finds the day with the lowest total price, and prints 
 * the daily percentage price difference.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task14.c -o task14
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int array_1[] = {4120, 3102, 2233, 7884, 9862, 1234, 8751, 1235, 1232, 1421};
    int array_2[] = {46920, 46802, 46830, 46705, 46392, 46644, 46642, 46371, 46806, 46820};
    int array_3[] = {4562, 2341, 5642, 5461, 1234, 1345, 1923, 1676, 1872, 1765};
    
    int len = (int)(sizeof(array_1) / sizeof(array_1[0]));
    
    int average[len];
    int day[len];
    int min;
    int date = 0;
    float percentage[len];

    for (int i = 0; i < len; i++)
    {
        average[i] = array_1[i] + array_2[i] + array_3[i];
        day[i] = i + 8;
    }

    min = average[0];
    for (int i = 1; i < len; i++)
    {
        if (average[i] < min)
        {
            min = average[i];
            date = i;
        }
    }
        
    percentage[0] = 0.0f;
    for (int i = 1; i < len; i++)
    {
        float diff = (float)(average[i] - average[i - 1]);
        percentage[i] = (diff / average[i - 1]) * 100.0f;
    }

    for (int i = 0; i < len; i++)
    {
        printf("The price change for Sep %2d is %7.2f%% \n", day[i], percentage[i]);
    }

    printf("\nThe profitable day is Sep %d and the price is %d\n\n", day[date], average[date]);

    return EXIT_SUCCESS;
}