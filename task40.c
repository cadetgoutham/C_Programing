/**
 * @file      : task40.c
 * @brief     : Complete and robust singly linked list manager implementation.
 * @note      : Compile command: gcc -Wall -Wextra -std=c11 task40.c -o task40
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
};

void display(const struct node *start) {
    if (start == NULL) {
        printf("List is empty.\n\n");
        return;
    }
    printf("List elements: ");
    while (start != NULL) {
        printf("%d ", start->info);
        start = start->link;
    }
    printf("\n\n");
}

void count(const struct node *start) {
    int cnt = 0;
    while (start != NULL) {
        cnt++;
        start = start->link;
    }
    printf("Number of elements = %d\n\n", cnt);
}

void search(const struct node *start, int data) {
    int pos = 1;
    while (start != NULL) {
        if (start->info == data) {
            printf("Item %d found at position %d\n\n", data, pos);
            return;
        }
        start = start->link;
        pos++;
    }
    printf("Item %d not found in list\n\n", data);
}

struct node *addatbeg(struct node *start, int data) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    if (tmp == NULL) return start;
    tmp->info = data;
    tmp->link = start;
    return tmp;
}

struct node *addatend(struct node *start, int data) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    if (tmp == NULL) return start;
    tmp->info = data;
    tmp->link = NULL;

    if (start == NULL) return tmp;
    struct node *p = start;
    while (p->link != NULL) {
        p = p->link;
    }
    p->link = tmp;
    return start;
}

struct node *addatpos(struct node *start, int data, int pos) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    if (tmp == NULL) return start;
    tmp->info = data;

    if (pos == 1) {
        tmp->link = start;
        return tmp;
    }

    struct node *p = start;
    for (int i = 1; i < pos - 1 && p != NULL; i++) {
        p = p->link;
    }

    if (p == NULL) {
        printf("There are less than %d elements\n\n", pos);
        free(tmp);
    } else {
        tmp->link = p->link;
        p->link = tmp;
    }
    return start;
}

struct node *del(struct node *start, int data) {
    if (start == NULL) {
        printf("List is empty\n\n");
        return NULL;
    }

    struct node *tmp;
    if (start->info == data) {
        tmp = start;
        start = start->link;
        free(tmp);
        return start;
    }

    struct node *p = start;
    while (p->link != NULL) {
        if (p->link->info == data) {
            tmp = p->link;
            p->link = tmp->link;
            free(tmp);
            return start;
        }
        p = p->link;
    }
    printf("\nElement %d not found\n\n", data);
    return start;
}

struct node *reverse(struct node *start) {
    struct node *prev = NULL;
    struct node *ptr = start;
    struct node *next = NULL;
    while (ptr != NULL) {
        next = ptr->link;
        ptr->link = prev;
        prev = ptr;
        ptr = next;
    }
    return prev;
}

void free_all(struct node *start) {
    while (start != NULL) {
        struct node *tmp = start->link;
        free(start);
        start = tmp;
    }
}

int main(void) {
    struct node *start = NULL;
    int choice = 0, data = 0, pos = 0;

    while (1) {
        printf("1. Create/Append End\n2. Display\n3. Count\n4. Search\n");
        printf("5. Add at Beginning\n6. Add at Position\n7. Delete Node\n8. Reverse List\n9. Quit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (choice == 9) break;
        switch (choice) {
            case 1:
                printf("Enter data value: ");
                if (scanf("%d", &data) == 1) start = addatend(start, data);
                break;
            case 2: display(start); break;
            case 3: count(start); break;
            case 4:
                printf("Enter search value: ");
                if (scanf("%d", &data) == 1) search(start, data);
                break;
            case 5:
                printf("Enter start value: ");
                if (scanf("%d", &data) == 1) start = addatbeg(start, data);
                break;
            case 6:
                printf("Enter value and position: ");
                if (scanf("%d %d", &data, &pos) == 2) start = addatpos(start, data, pos);
                break;
            case 7:
                printf("Enter target deletion value: ");
                if (scanf("%d", &data) == 1) start = del(start, data);
                break;
            case 8:
                start = reverse(start);
                printf("List reversed successfully.\n\n");
                break;
            default: printf("Unknown selection.\n\n");
        }
    }
    free_all(start);
    return EXIT_SUCCESS;
}