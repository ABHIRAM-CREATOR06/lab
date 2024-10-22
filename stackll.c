#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
}* top = NULL;

void push() {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newNode->data);
    newNode->link = top;
    top = newNode;
    printf("Insertion successful\n");
}

void pop() {
    if (top == NULL) {
        printf("Stack is empty\n");
    } else {
        struct node* temp = top;
        top = top->link;
        printf("Popped element: %d\n", temp->data);
    }
}

void peek() {
    if (top == NULL) {
        printf("Stack is empty\n");
    } else {
        printf("Top element is %d\n", top->data);
    }
}

void display() {
    if (top == NULL) {
        printf("Stack is empty\n");
    } else {
        struct node* temp = top;
        printf("Stack elements: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

void main() {
    int choice;
    do {
        printf("\nStack operations:\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("0. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 0:
                printf("Exiting program\n");
                break;
            default: 
                printf("Invalid choice\n");
        }
    } while (choice != 0);
}