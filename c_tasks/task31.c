/**
 * @file      : task31.c
 * @brief     : Generates a sequential chain list tracking configuration,
 * reverses the references, and traces details back to the console.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task31.c -o task31
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node* insert(struct node *head, struct node **tail, int x) {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL) return head;
    p->data = x;
    p->link = NULL;
    
    if (head == NULL) {
        head = p;
        *tail = p;
    } else {
        (*tail)->link = p;
        *tail = p;
    }
    return head;
}

void traverse(const struct node *node_target) {
    printf("The list is: ");
    while (node_target != NULL) {
        printf("%d->", node_target->data);
        node_target = node_target->link;
    }
    printf("NULL\n");
}

struct node *reverse(struct node *p) {
    struct node *prev = NULL;
    struct node *current = p;
    struct node *next_node = NULL;
    
    while (current != NULL) {
        next_node = current->link;
        current->link = prev;
        prev = current;
        current = next_node;
    }
    return prev;
}

void free_list(struct node *head_node) {
    struct node *curr = head_node;
    while (curr != NULL) {
        struct node *next = curr->link;
        free(curr);
        curr = next;
    }
}

int main(void) {
    struct node *local_head = NULL;
    struct node *local_tail = NULL;
    int elements_count = 0;
    int input_val = 0;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &elements_count) != 1 || elements_count <= 0) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < elements_count; i++) {
        printf("Enter value [%d]: ", i + 1);
        if (scanf("%d", &input_val) == 1) {
            local_head = insert(local_head, &local_tail, input_val);
        }
    }
    
    printf("\n[Original State Map]\n");
    traverse(local_head);
    
    local_head = reverse(local_head);
    
    printf("\n[Reversed State Map]\n");
    traverse(local_head);
    
    free_list(local_head);
    return EXIT_SUCCESS;
}