/**
 * @file      : task9.c
 * @brief     : Parses a hardware MAC address to accurately classify it 
 * as Unicast, Multicast, or Broadcast using proper byte-level logic.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task9.c -o task9
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    char raw_input[100];
    unsigned int bytes[6];

    printf("Enter The MAC Address (e.g., AA:BB:CC:DD:EE:FF or 12-34-56-78-9A-BC):\n");
    
    /* Safely read string input to avoid terminal buffer issues */
    if (fgets(raw_input, sizeof(raw_input), stdin) == NULL) {
        printf("Error reading input stream.\n");
        return EXIT_FAILURE;
    }

    /* * Parse the raw string into numerical integer byte blocks.
     * Tries colon separators first, then falls back to hyphen separators.
     */
    int parsed = sscanf(raw_input, "%x:%x:%x:%x:%x:%x", 
                        &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5]);
                        
    if (parsed != 6) {
        parsed = sscanf(raw_input, "%x-%x-%x-%x-%x-%x", 
                            &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5]);
    }

    /* Verification guard: A valid MAC address must contain exactly 6 hexadecimal bytes */
    if (parsed != 6 || bytes[0] > 0xFF || bytes[1] > 0xFF || bytes[2] > 0xFF || 
        bytes[3] > 0xFF || bytes[4] > 0xFF || bytes[5] > 0xFF) {
        printf("\nError: Invalid MAC address format configuration.\n");
        return EXIT_FAILURE;
    }

    /* * Evaluation Phase:
     * 1. Broadcast check: All 48 bits must be high (FF:FF:FF:FF:FF:FF)
     */
    if (bytes[0] == 0xFF && bytes[1] == 0xFF && bytes[2] == 0xFF && 
        bytes[3] == 0xFF && bytes[4] == 0xFF && bytes[5] == 0xFF) {
        printf("\nThe given MAC Address is a BROADCAST MAC Address...\n");
    }
    /* * 2. Unicast vs. Multicast check: Inspect the Least Significant Bit (LSB) 
     * of the very first octet (bytes[0]).
     * - LSB == 1 -> Multicast Group Address
     * - LSB == 0 -> Unicast Individual Address
     */
    else if ((bytes[0] & 0x01) == 1) {
        printf("\nThe given MAC Address is a MULTICAST MAC Address...\n");
    } 
    else {
        printf("\nThe given MAC Address is a UNICAST MAC Address...\n");
    }

    return EXIT_SUCCESS;
}