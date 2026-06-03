/**
  * @file      : thread_id.c
  * @brief     : Demonstrates safe POSIX thread creation, dynamic argument
  * passing, orderly worker synchronization utilizing mutex locks,
  * and systematic resource cleanup.
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Global synchronization primitive for console output serialization */
pthread_mutex_t console_mutex;

/**
 * @brief Thread entry point function execution routing.
 * @param ptr Pointer to dynamically allocated integer tracking creation index.
 */
void *thread_worker_func(void *ptr)
{
    if (ptr == NULL)
    {
        return NULL;
    }

    int iteration_id = *((int *)ptr);

    /* Serialize access to standard output streams to prevent scrambled printing */
    pthread_mutex_lock(&console_mutex);
    
    /* Safely print the current thread ID using standard portable unsigned long handling */
    printf("Hello from worker thread %lu - I was created in iteration %d\n", 
           (unsigned long)pthread_self(), iteration_id);
    
    pthread_mutex_unlock(&console_mutex);
    
    /* Critical Fix: Free heap allocation inside thread lifecycle context to prevent leaks */
    free(ptr);
    
    return NULL;
}

int main(int argc, char *argv[])
{
    /* 1. Defensive Guard Clause: Verify input constraints exist before casting pointers */
    if (argc < 2)
    {
                printf("Error: Missing execution parameters.\n");
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    int total_threads = atoi(argv[1]);
    if (total_threads <= 0)
    {
        printf("Error: Thread count assignment parameter must be greater than 0.\n");
        return 1;
    }

    /* Track thread identifiers using dynamically allocated array */
    pthread_t *thread_pool = malloc(sizeof(pthread_t) * total_threads);
    if (thread_pool == NULL)
    {
        printf("System Error: Dynamic execution memory pool exhaustion allocation failure.\n");
        return 1;
    }

    /* Initialize POSIX synchronization component */
    if (pthread_mutex_init(&console_mutex, NULL) != 0)
    {
        printf("System Error: Mutex primitive subsystem failed initialization tracking routines.\n");
        free(thread_pool);
        return 1;
    }
    
    /* 2. Worker Generation Spawning Dispatch Sequence Loop */
    for (int current_index = 0; current_index < total_threads; current_index++)
    {
        int iteration_display_number = current_index + 1;
        
        int *heap_argument_payload = (int *)malloc(sizeof(int));
        if (heap_argument_payload == NULL)
        {
            printf("Runtime Error: Argument context allocation failure on iteration %d.\n", iteration_display_number);
            break;
        }
        *heap_argument_payload = iteration_display_number;
        
        /* Spawn thread worker safely passing allocated integer payload state tracker */
        if (pthread_create(&thread_pool[current_index], NULL, thread_worker_func, (void *)heap_argument_payload) != 0)
        {
            printf("Runtime Error: Unable to instantiate thread index identity marker %d.\n", current_index);
            free(heap_argument_payload); // Clean up allocations if creation fails
            continue;
        }

        pthread_mutex_lock(&console_mutex);
        printf("I am the Main Thread, created new thread (%lu) in iteration %d\n", 
               (unsigned long)thread_pool[current_index], iteration_display_number);
        pthread_mutex_unlock(&console_mutex);
        
        /* Yield scheduler sequence context every 4 loops */
        if (iteration_display_number % 4 == 0)
        {
            sleep(1);
        }
    }
    
    /* 3. Thread Synchronization Pipeline Consolidation Collection */
    for (int current_index = 0; current_index < total_threads; current_index++)
    {
        /* Verify elements exist before executing synchronization collection loops */
        if (thread_pool[current_index] != 0)
        {
            pthread_join(thread_pool[current_index], NULL);
        }
    }
    
    /* 4. Complete System Resource Freeing Cleanups Procedures */
    pthread_mutex_destroy(&console_mutex);
    free(thread_pool);
    
    printf("\nSuccessfully processed execution timeline. Gracefully shutting down application.\n");
    return 0;
}