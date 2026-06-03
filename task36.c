/**
 * @file      : task36.c
 * @brief     : Divides an existing linked list into two smaller sub-lists containing alternate nodes.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task36.c -o task36
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node* push(struct node *head, struct node **tail, int element, int *node_count) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) return head;
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
    const struct node *ptr = head;
    printf("{");
    while (ptr != NULL) {
        printf("%d", ptr->data);
        if (ptr->link != NULL) printf("->");
        ptr = ptr->link;
    }
    printf("}");
}

void split_alternate(struct node *head) {
    if (head == NULL) {
        printf("\nList is empty. Cannot split.\n");
        return;
    }

    struct node *sub1 = NULL, *tail1 = NULL;
    struct node *sub2 = NULL, *tail2 = NULL;
    struct node *current = head;
    int index = 0;

    while (current != NULL) {
        struct node *next_node = current->link; // save next link
        
        /* Deep copy nodes into sub-lists to preserve original list integrity */
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if (new_node == NULL) return;
        new_node->data = current->data;
        new_node->link = NULL;

        if (index % 2 == 0) {
            if (sub1 == NULL) { sub1 = new_node; tail1 = new_node; }
            else { tail1->link = new_node; tail1 = new_node; }
        } else {
            if (sub2 == NULL) { sub2 = new_node; tail2 = new_node; }
            else { tail2->link = new_node; tail2 = new_node; }
        }
        current = next_node;
        index++;
    }

    printf("\nSublist 1 (Even Indices): "); display(sub1);
    printf("\nSublist 2 (Odd Indices): ");  display(sub2);
    printf("\n");

    /* Free temporary sublist structures */
    while(sub1) { struct node *t = sub1->link; free(sub1); sub1 = t; }
    while(sub2) { struct node *t = sub2->link; free(sub2); sub2 = t; }
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
    int count = 0, choice = 0, element_input = 0, node_count = 0;
    
    printf("Enter initial node count: ");
    if (scanf("%d", &count) != 1 || count < 0) return EXIT_FAILURE;
    
    for (int i = 0; i < count; i++) {
        printf("Enter element [%d of %d]: ", i + 1, count);
        if (scanf("%d", &element_input) == 1) {
            head = push(head, &tail, element_input, &node_count);
        }
    }
    
    while (1) {
        printf("\n--- Alternate Menu ---\n1. ADD ITEM\n2. DISPLAY\n3. SPLIT ALTERNATE\n4. COUNT\n5. EXIT\nEnter selection: ");
        if (scanf("%d", &choice) != 1) break;
        
        if (choice == 1) {
            printf("Enter item value to add: ");
            if (scanf("%d", &element_input) == 1) {
                head = push(head, &tail, element_input, &node_count);
            }
        } else if (choice == 2) {
            printf("\nFull list: "); display(head); printf("\n");
        } else if (choice == 3) {
            split_alternate(head);
        } else if (choice == 4) {
            printf("\nThe node count = %d\n", node_count);
        } else if (choice == 5) {
            break;
        }
    }
    
    free_list(head);
    return EXIT_SUCCESS;
}