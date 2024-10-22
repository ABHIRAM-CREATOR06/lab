#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
} *front = NULL, *rear = NULL, *current = NULL;

int main() {
    int choice, ele, cont = 0; 
    printf("\nChoices : \n");
    printf("1.Enqueue: ");
    printf("2.Dequeue: ");
    printf("3.Peek: ");
    printf("4.Display ");
    printf("5.Exit ");
    do {
        printf("\nenter choice  : ");
        scanf("%d", &choice); 

        switch (choice) {
            case 1:
                current = (struct node *)malloc(sizeof(struct node));
                printf("enter element to be inserted :");
                scanf("%d", &ele);
                current->data = ele;
                current->link = NULL;
                if (front == NULL) {
                    front = rear = current;
                } else {
                    rear->link = current;
                    rear = current;
                    printf("element inserted successfully\n");
                }
                break;
            case 2:
                printf("pop option selected\n");
                if (front == NULL) {
                    printf("Queue is empty\n");
                } else {
                    current = front;
                    front = front->link;
                    printf("deleted element is %d\n", current->data);
                    free(current); 
                }
                break;
            case 3:
                printf("peek that's the frontmost element is ");
                if (front == NULL) {
                    printf("queue is empty\n");
                } else {
                    printf("%d\n", front->data);
                }
                break;
            case 4:
                printf("Display option\n");
                current = front;
                while (current != NULL) {
                    printf("%d ", current->data); 
                    current = current->link;
                }
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 5); // Use choice for the loop condition

    return 0; // Return 0 from main
}
