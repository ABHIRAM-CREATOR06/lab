// singly linked list
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
} *first = NULL, *last = NULL, *current = NULL, *I, *prev;

void main() {
    int choice, cont, ele;
    cont = 1; // Initialize cont to enter the loop
    printf("\n Available options \n");
    printf("1. Creation\n");
    printf("2. Insert at the beginning\n");
    printf("3. Insert in between\n");
    printf("4. Insert at the end\n");
    printf("5. Delete\n");
    printf("8. Display\n");

    do {
        printf("\n Enter your choice \n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n Enter the data \n");
                scanf("%d", &ele); // Read the data into ele
                I = (struct node *)malloc(sizeof(struct node));
                I->data = ele;
                I->link = NULL;
                if (first == NULL) {
                    first = I; // Initialize first if the list is empty
                    last = I; // Also set last to the new node
                    printf("Successful Creation\n");
                } else {
                    last->link = I;
                    last = I;
                    printf("Node added to the end\n");
                }
                break;
            case 2:
                printf("\n Enter the data to insert at front\n");
                scanf("%d", &ele);
                I = (struct node *)malloc(sizeof(struct node));
                I->data = ele;
                I->link = first; // Link new node to the current first
                first = I; // Update first to new node
                printf("Insertion at front done\n");
                break;
            case 3:
                printf("Enter the reference element:\n");
                scanf("%d", &ele);
                current = first;
                while (current != NULL && current->data != ele) {
                    prev = current;
                    current = current->link;
                }
                if (current == NULL) {
                    printf("Reference element not found\n");
                } else {
                    I = (struct node *)malloc(sizeof(struct node));
                    printf("Enter the data to insert:\n");
                    scanf("%d", &ele);
                    I->data = ele; 
                    I->link = current->link;
                    current->link = I;
                    printf("Insertion at in-between done\n");
                }
                break;
            case 4:
                printf("Enter a number to insert at the end:\n");
                scanf("%d", &ele);
                I = (struct node *)malloc(sizeof(struct node));
                I->data = ele;
                I->link = NULL;
                if (first == NULL) {
                    first = I; 
                    last = I; 
                    printf("Node added to the end\n");
                } else {
                    last->link = I;
                    last = I;
                    printf("Node added to the end\n");
                }
                break;
            case 5:
                printf("Enter element to delete:\n");
                scanf("%d", &ele);
                current = first;
                prev = NULL;
                while (current != NULL && current->data != ele) {
                    prev = current;
                    current = current->link;
                }
                if (current == NULL) {
                    printf("Element not found\n");
                } else {
                    if (current == first) {
                        printf("Element deleted at first\n");
                        first = current->link;
                        free(current);
                    } else if (current == last) {
                        printf("Element deleted at last\n");
                        prev->link = NULL;
                        last = prev;
                        free(current);
                    } else {
                        printf("Element deleted in between\n");
                        prev->link = current->link;
                        free(current);
                    }
                }
                break;
            case 8:
                current = first;
                printf("Elements in the list are: ");
                while (current != NULL) {
                    printf("%d ", current->data);
                    current = current->link;
                }
                printf("\n");
                break;
            default:
                printf("Invalid choice\n");
        }
        printf("Do you want to continue? (1 for yes, 0 for no)\n");
        scanf("%d", &cont);
    } while (cont == 1);
}