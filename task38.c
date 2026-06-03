/**
 * @file      : task38.c
 * @brief     : Extracts character frequencies from strings and lists them alphabetically.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task38.c -o task38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char letter;
    int count;
    struct node *link;
};

struct node* push(struct node *head, struct node **tail, char ch, int number) {
    struct node *ptr2 = head;
    while (ptr2 != NULL) {
        if (ptr2->letter == ch) {
            return head; /* Already tracked */
        }
        ptr2 = ptr2->link;
    }

    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) return head;
    ptr->letter = ch;
    ptr->count = number;
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
    printf("\nCharacter Occurrence Tracker:\n");
    while (ptr != NULL) {
        printf("['%c' : %d times] -> ", ptr->letter, ptr->count);
        ptr = ptr->link;
    }
    printf("END\n");
}

void sort_and_display(struct node *head) {
    if (head == NULL) return;
    struct node *ptr1;
    struct node *ptr2;
    char temp_char;
    int temp_count;
    
    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->link) {
        for (ptr2 = ptr1->link; ptr2 != NULL; ptr2 = ptr2->link) {
            if (ptr1->letter > ptr2->letter) {
                temp_char = ptr1->letter;
                ptr1->letter = ptr2->letter;
                ptr2->letter = temp_char;
                
                temp_count = ptr1->count;
                ptr1->count = ptr2->count;
                ptr2->count = temp_count;
            }
        }
    }
    display(head);
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
    
    printf("Enter text line sequence: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    for (size_t i = 0; i < len; i++) {
        char temp = input[i];
        if (temp == ' ' || temp == '\t') continue; /* Skip blank spaces */
        
        int match_count = 0;
        for (size_t j = 0; j < len; j++) {
            if (input[j] == temp) {
                match_count++;
            }
        }
        head = push(head, &tail, temp, match_count);
    }
    
    sort_and_display(head);
    free_list(head);
    
    return EXIT_SUCCESS;
}