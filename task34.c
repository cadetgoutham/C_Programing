/**
 * @file      : task34.c
 * @brief     : Implements a clean FIFO structured processing queue pipeline.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task34.c -o task34
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

void enqueue(struct node **head, struct node **tail, int element) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) return;
    ptr->data = element;
    ptr->link = NULL;
    
    if (*head == NULL) {
        *head = ptr;
        *tail = ptr;
    } else {
        (*tail)->link = ptr;
        *tail = ptr;
    }
}

void display(const struct node *head) {
    printf("\nThe queue execution tracking layout: ");
    while (head != NULL) {
        printf("%d->", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

void dequeue(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("\nQueue Underflow! Operation terminated.\n");
        return;
    }
    struct node *temp = *head;
    *head = (*head)->link;
    
    if (*head == NULL) {
        *tail = NULL;
    }
    
    printf("\nSuccessfully processed and removed data sequence item: [%d]\n", temp->data);
    free(temp);
}

void free_queue(struct node *head) {
    while (head != NULL) {
        struct node *tmp = head->link;
        free(head);
        head = tmp;
    }
}

int main(void) {
    struct node *q_head = NULL;
    struct node *q_tail = NULL;
    int choice = 0;
    int data_token = 0;
    
    printf("Pre-loading setup initialization values...\n");
    for (int i = 0; i < 3; i++) {
        printf("Initialize element item [%d of 3]: ", i + 1);
        if (scanf("%d", &data_token) == 1) {
            enqueue(&q_head, &q_tail, data_token);
        }
    }
    
    while (1) {
        printf("\n--- Operational Mode Matrix ---\n1. ENQUEUE\n2. DEQUEUE\n3. DISPLAY\n4. EXIT\nSelect mode: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
        
        if (choice == 1) {
            printf("Enter parameter value to verify: ");
            if (scanf("%d", &data_token) == 1) {
                enqueue(&q_head, &q_tail, data_token);
            }
        } else if (choice == 2) {
            dequeue(&q_head, &q_tail);
        } else if (choice == 3) {
            display(q_head);
        } else if (choice == 4) {
            break;
        } else {
            printf("Selection out of scale matrix boundaries.\n");
        }
    }
    
    free_queue(q_head);
    return EXIT_SUCCESS;
}