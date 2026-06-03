/**
 * @file      : task30.c
 * @brief     : Extracts individual integer elements into a structured linear LIFO stack.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task30.c -o task30
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

/* File isolated root reference track */
static struct node *head = NULL;

void push(int element) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Stack allocation system fault.\n");
        return;
    }
    ptr->data = element;
    ptr->link = head;
    head = ptr;
}

void display(void) {
    struct node *ptr = head;
    printf("Output Sequence: ");
    while (ptr != NULL) {
        printf("%d->", ptr->data);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

void free_memory_pool(void) {
    struct node *current = head;
    while (current != NULL) {
        struct node *next_node = current->link;
        free(current);
        current = next_node;
    }
    head = NULL;
}

int main(void) {
    int number;
    
    printf("Enter the number: ");
    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }
    
    if (number == 0) {
        push(0);
    } else {
        /* Capture absolute evaluation scope path contexts */
        int temp = abs(number);
        while (temp > 0) {
            push(temp % 10);
            temp /= 10;
        }
    }
    
    display();
    free_memory_pool();
    
    return EXIT_SUCCESS;
}