/**
  * @file      : task43.c
  * @brief     : Demonstrates an enhanced callback pattern in C. Passing data 
  * payloads through a function pointer and processing return states.
  */

#include <stdio.h>

// 1. Target function now accepts a configuration integer and returns a status code
int my_event_handler(int event_id) 
{
    printf("-> [Handler] Processing Event ID: %d...\n", event_id);
    // Simulate successful processing logic
    return 0; 
}

// 2. Callback engine accepts the function pointer alongside an active data payload
void process_system_event(int (*callback_ptr)(int), int payload_data) 
{
    printf("[Engine] Registering callback and initializing event dispatch...\n");
    
    // Modern shorthand notation to invoke the function pointer with data
    int status = callback_ptr(payload_data);   
    
    if (status == 0) {
        printf("[Engine] Callback executed successfully.\n");
    } else {
        printf("[Engine] Callback reported an error code: %d\n", status);
    }
}

int main(void) 
{
    // Define the function pointer type explicitly matching our new signature
    int (*ptr)(int) = my_event_handler;
    
    // Dispatch event tracking with a simulated event ID (e.g., 404)
    process_system_event(ptr, 404);
    
    return 0;
}