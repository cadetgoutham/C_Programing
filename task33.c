/**
 * @file      : task33.c
 * @brief     : Implements a clean LIFO structured processing pipeline.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task33.c -o task33
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node* push(struct node *head, int element) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Allocation error.\n");
        return head;
    }
    ptr->data = element;
    ptr->link = head;
    return ptr;
}

void display(const struct node *head) {
    printf("\nThe stack layout profile: ");
    while (head != NULL) {
        printf("%d->", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

struct node* pull(struct node *head) {
    if (head == NULL) {
        printf("\nStack Underflow! Pull operation dropped.\n");
        return NULL;
    }
    struct node *next_node = head->link;
    printf("\nSuccessfully popped data segment item: [%d]\n", head->data);
    free(head);
    return next_node;
}

void free_stack(struct node *head) {
    while (head != NULL) {
        struct node *tmp = head->link;
        free(head);
        head = tmp;
    }
}

int main(void) {
    struct node *stack_root = NULL;
    int choice = 0;
    int element_input = 0;
    
    printf("Initializing processing engine configuration states...\n");
    for (int i = 0; i < 3; i++) {
        printf("Seed configuration input element [%d of 3]: ", i + 1);
        if (scanf("%d", &element_input) == 1) {
            stack_root = push(stack_root, element_input);
        }
    }
    
    while (1) {
        printf("\n--- Operational Mode Matrix ---\n1. PUSH\n2. POP (PULL)\n3. DISPLAY\n4. EXIT\nSelect mode: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
        
        if (choice == 1) {
            printf("Enter item value to PUSH: ");
            if (scanf("%d", &element_input) == 1) {
                stack_root = push(stack_root, element_input);
            }
        } else if (choice == 2) {
            stack_root = pull(stack_root);
        } else if (choice == 3) {
            display(stack_root);
        } else if (choice == 4) {
            break;
        } else {
            printf("Selection out of matrix scale boundaries.\n");
        }
    }
    
    free_stack(stack_root);
    return EXIT_SUCCESS;
}