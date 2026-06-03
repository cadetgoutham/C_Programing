/**
 * @file      : task3.c
 * @brief     : Comprehensive demonstration of C storage classes (auto, register, static, extern).
 * Illustrates variable scopes, memory lifetimes, and compilation linkage rules.
 * @note      : Compiles cleanly with standard C flags: gcc -Wall -Wextra -std=c11 task3.c
 */

#include <stdio.h>
#include <stdlib.h>

/* Global variables (External Linkage by default) */
int global_number = 500;

/* Internal Linkage: Visible only within this translation unit (.c file) */
static int static_global_number = 1;

/**
 * @brief Demonstrates the 'auto' storage class (Default for local variables).
 * Illustrates lexical scoping where block-scoped variables shadow outer declarations.
 */
void demonstrate_auto_class(void) {
    printf("\n--- [1] Auto Storage Class (Block Scoping & Shadowing) ---\n");
    
    auto int scope_number = 9; /* Primary function-level variable */
    
    {
        auto int scope_number = 8; /* Shadows the outer scope_number (9) */
        
        {
            auto int scope_number = 6; /* Shadows the outer scope_number (8) */
            printf("In third (innermost) block, auto number  = %d\n", scope_number);
        }
        
        printf("In second (middle) block, auto number     = %d\n", scope_number);
    }
    
    printf("In first (function-level) block, auto number = %d\n", scope_number);
}

/**
 * @brief Demonstrates the 'register' storage class.
 * Hints to the compiler to store the variable in a CPU register for fast access.
 * Crucial Rule: Register variables do not reside in RAM, so they lack a memory address.
 */
void demonstrate_register_class(void) {
    printf("\n--- [2] Register Storage Class (CPU Allocation Hint) ---\n");
    
    register int register_number = 10;
    
    printf("Value of number requested for register space = %d\n", register_number);
    
    /* * COMPILER ARCHITECTURE NOTE:
     * Un-commenting the code below will trigger a compilation failure: 
     * "error: address of register variable requested"
     *
     * int *ptr = &register_number; 
     * printf("Address of register = %p\n", (void*)ptr);
     */
    printf("Note: Memory address (&) extraction is strictly illegal for register-allocated space.\n");
}

/**
 * @brief Demonstrates the 'static' storage class for local variables.
 * Local static variables are initialized exactly once and preserve their data state 
 * across sequential function invocations throughout the program's lifecycle.
 */
void demonstrate_static_class(void) {
    /* Initialized once at application startup, not on every function call */
    static int local_static_counter = 0; 
    
    {
        static int inner_static_block = 2;
        printf("Static local block value                 = %d\n", inner_static_block);
        inner_static_block++;
        
        printf("Global static tracker value (Before Iner) = %d\n", static_global_number);
        static_global_number++;
    }
    
    printf("Global static tracker value (After Incr)  = %d\n", static_global_number);
    printf("Local static execution function counter   = %d\n", local_static_counter);
    
    local_static_counter++;
}

/**
 * @brief Demonstrates the 'extern' storage class.
 * Points to a global variable defined elsewhere in the program or global runtime namespace.
 */
void demonstrate_extern_class(void) {
    /* Refers to the global variable instantiated outside function scopes */
    extern int global_number; 
    
    printf("Extern global resource resolved value     = %d\n", global_number);
    global_number++;                               
    printf("Extern global variable state incremented  = %d\n", global_number);
}

int main(void) {
    /* 1. Run scoping visualization */
    demonstrate_auto_class();
    
    /* 2. Run register address constraints test */
    demonstrate_register_class();
    
    /* * 3. Run Static behaviors. 
     * We invoke this multiple times to clearly see how values persist in memory.
     */
    printf("\n--- [3] Static Storage Class (Persistent Memory State) ---\n");
    printf(">> Invoking Static Routine: Call #1\n");
    demonstrate_static_class();
    
    printf("\n>> Invoking Static Routine: Call #2 (Notice value persistence)\n");
    demonstrate_static_class();
    
    /* * 4. Run Extern tracking.
     * Invoked twice to show mutations to global memory context across boundaries.
     */
    printf("\n--- [4] Extern Storage Class (Global Variable Linkage) ---\n");
    printf(">> Invoking Extern Routine: Call #1\n");
    demonstrate_extern_class();
    
    printf("\n>> Invoking Extern Routine: Call #2\n");
    demonstrate_extern_class();
    
    return EXIT_SUCCESS;
}