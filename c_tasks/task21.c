/**
 * @file      : task21.c
 * @brief     : Reads a sentence and reverses every odd-positioned word.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task21.c -o task21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invert_token(char *word) {
    int len = (int)strlen(word);
    for (int i = 0; i < len / 2; i++) {
        char temp = word[i];
        word[i] = word[len - 1 - i];
        word[len - 1 - i] = temp;
    }
}

int main(void) {
    char raw_sentence[200];
    
    printf("Enter the string sentence:\n");
    if (fgets(raw_sentence, sizeof(raw_sentence), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    raw_sentence[strcspn(raw_sentence, "\r\n")] = '\0';
    
    /* * ROBUST TOKENIZATION ENGINE:
     * Splitting words via standard strtok tracks layout boundaries natively,
     * ensuring odd-positioned words are reversed correctly, including the final word.
     */
    char *token = strtok(raw_sentence, " ");
    int word_position = 1;
    
    while (token != NULL) {
        if (word_position % 2 != 0) {
            invert_token(token);
        }
        printf("%s ", token);
        token = strtok(NULL, " ");
        word_position++;
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}