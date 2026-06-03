/**
 * @file      : task35.c
 * @brief     : Creates a linked list, inserts a new node into its correct sorted position,
 * and counts total elements.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task35.c -o task35
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node* push(struct node *head, struct node **tail, int element, int *node_count) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }
    ptr->data = element;
    ptr->link = NULL;
    
    if (head == NULL) {
        head = ptr;
        *tail = ptr;
    } else {
        (*tail)->link = ptr;
        *tail = ptr;
    }
    if (node_count) (*node_count)++;
    return head;
}

void display(const struct node *head) {
    printf("\nThe linked list layout: ");
    const struct node *ptr = head;
    while (ptr != NULL) {
        printf("%d->", ptr->data);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

struct node* insert_in_sortedLL(struct node *head, int element, int *node_count) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) return head;
    new_node->data = element;
    new_node->link = NULL;

    if (head == NULL || head->data >= element) {
        new_node->link = head;
        head = new_node;
    } else {
        struct node *current = head;
        while (current->link != NULL && current->link->data < element) {
            current = current->link;
        }
        new_node->link = current->link;
        current->link = new_node;
    }
    if (node_count) (*node_count)++;
    return head;
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
    int count = 0;
    int choice = 0;
    int element_input = 0;
    int node_count = 0;
    
    printf("Enter number of initial nodes: ");
    if (scanf("%d", &count) != 1 || count < 0) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter element [%d of %d]: ", i + 1, count);
        if (scanf("%d", &element_input) == 1) {
            head = push(head, &tail, element_input, &node_count);
        }
    }
    
    while (1) {
        printf("\n--- Operational Menu ---\n1. ADD ITEM\n2. DISPLAY\n3. SORT & ADD\n4. COUNT\n5. EXIT\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;
        
        if (choice == 1) {
            printf("Enter item value to add: ");
            if (scanf("%d", &element_input) == 1) {
                head = push(head, &tail, element_input, &node_count);
            }
        } else if (choice == 2) {
            display(head);
        } else if (choice == 3) {
            printf("Enter value to insert in sorted position: ");
            if (scanf("%d", &element_input) == 1) {
                head = insert_in_sortedLL(head, element_input, &node_count);
            }
        } else if (choice == 4) {
            printf("\nThe node count = %d\n", node_count);
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid selection.\n");
        }
    }
    
    free_list(head);
    return EXIT_SUCCESS;
}