/**
  * @file      : thread_sync.c
  * @brief     : Demonstrates safe POSIX thread instantiation, synchronized
  * sharing of internal static state variables using mutex locks, 
  * and systematic sequence resource collection.
  */

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/* Global synchronization primitive for coordinating shared state modifications */
pthread_mutex_t state_mutex;

/**
 * @brief Thread entry routine function.
 * @param arg Pointer to a character array passed from the creator context.
 * @return void* Returns NULL upon orderly completion.
 */
void *thread_worker_func(void *arg)
{
    const char *message_payload = (const char *)arg;

    /* 1. Acquire mutex lock before accessing or modifying the shared static counter */
    pthread_mutex_lock(&state_mutex);
    
    /* Shared global/static context state component protected by the critical section */
    static int global_thread_counter = 1;
    
    printf("Worker Thread %d : %s\n", global_thread_counter, message_payload);
    
    global_thread_counter++;
    
    /* 2. Release mutex lock to allow other waiting threads to enter the critical section */
    pthread_mutex_unlock(&state_mutex);
    
    return NULL;
}

int main(void)
{
    /* Clear matrix initialization for text tracking assets */
    char text_payloads[][10] = {"hello", "world", "bye"};
    
    /* Expanded array to correctly hold all worker threads initialized by the loop */
    pthread_t worker_threads[2];
    
    /* Initialize the POSIX synchronization variable */
    if (pthread_mutex_init(&state_mutex, NULL) != 0)
    {
        printf("System Error: Mutex primitive failed to initialize.\n");
        return 1;
    }
    
    /* 3. Thread Spawning Loop Dispatch Pipeline */
    for (int thread_index = 0; thread_index < 2; thread_index++)
    {
        if (pthread_create(&worker_threads[thread_index], NULL, thread_worker_func, (void *)text_payloads[thread_index]) != 0)
        {
            printf("Runtime Error: Failed to instantiate thread index %d\n", thread_index);
        }
        
        /* Yield execution timeline to allow the operating system scheduler to balance threads */
        sleep(1);
    }
    
    /* 4. Ensure all spawned execution threads finish before moving main context */
    for (int thread_index = 0; thread_index < 2; thread_index++)
    {
        pthread_join(worker_threads[thread_index], NULL);
    }
    
    printf("Main Function  : %s\n", text_payloads[2]);
    
    /* 5. Deallocate and release standard system mutex resources cleanly */
    pthread_mutex_destroy(&state_mutex);
    
    return 0;
}