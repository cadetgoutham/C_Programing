/**
 * @file      : task37.c
 * @brief     : Parses a sentence into individual word nodes, sorts them alphabetically,
 * and prints them out using structured list handling.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task37.c -o task37
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char words[20];
    struct node *link;
};

struct node* push(struct node *head, struct node **tail, const char *word) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) return head;
    
    strncpy(ptr->words, word, sizeof(ptr->words) - 1);
    ptr->words[sizeof(ptr->words) - 1] = '\0';
    ptr->link = NULL;
    
    if (head == NULL) {
        head = ptr;
        *tail = ptr;
    } else {
        (*tail)->link = ptr;
        *tail = ptr;
    }
    return head;
}

void display(const struct node *head) {
    const struct node *ptr = head;
    while (ptr != NULL) {
        printf("%s", ptr->words);
        if (ptr->link != NULL) printf(" -> ");
        ptr = ptr->link;
    }
    printf("\n");
}

void sort_list(struct node *head) {
    if (head == NULL) return;
    char temp[20];
    struct node *ptr1;
    struct node *ptr2;
    
    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->link) {
        for (ptr2 = ptr1->link; ptr2 != NULL; ptr2 = ptr2->link) {
            if (strcmp(ptr1->words, ptr2->words) > 0) {
                strncpy(temp, ptr1->words, sizeof(temp) - 1);
                temp[sizeof(temp) - 1] = '\0';
                
                strncpy(ptr1->words, ptr2->words, sizeof(ptr1->words) - 1);
                ptr1->words[sizeof(ptr1->words) - 1] = '\0';
                
                strncpy(ptr2->words, temp, sizeof(ptr2->words) - 1);
                ptr2->words[sizeof(ptr2->words) - 1] = '\0';
            }
        }
    }
}

void free_list(struct node *head) {
    while (head != NULL) {
        struct node *tmp = head->link;
        free(head);
        head = tmp;
    }
}

int main(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    char input[100];
    char *token = NULL;
    char *saveptr = NULL;
    
    printf("Enter the sentence to sort: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Strip trailing newline character if present */
    input[strcspn(input, "\n")] = '\0';
    
    token = strtok_r(input, " ,.-", &saveptr);
    while (token != NULL) {
        head = push(head, &tail, token);
        token = strtok_r(NULL, " ,.-", &saveptr);
    }
    
    printf("\nOriginal Word Order:\n");
    display(head);
    
    sort_list(head);
    
    printf("\nAlphabetically Sorted Word Order:\n");
    display(head);
    
    free_list(head);
    return EXIT_SUCCESS;
}