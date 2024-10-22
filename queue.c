#include <stdio.h>
#define s 5
int q[s];
int front = -1, rear = -1; // Initialize front and rear

int main() { // Change void main() to int main()
    printf("Queue using array\n");
    int choice, e, c;
    printf("AVAILABLE OPTIONS\n");
    printf("1.ENQUEUE \n2.DEQUEUE \n3.PEEK\n4.DISPLAY\n");
    
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the element to be inserted: ");
                scanf("%d", &e);
                if (rear == s - 1) {
                    printf("Queue is full\n"); // Correct message for full queue
                } else {
                    if (front == -1) { // Queue was empty
                        front = rear = 0;
                    } else {
                        rear++;
                    }
                    q[rear] = e; // Insert the element in the queue
                    printf("Element inserted successfully\n");
                }
                break;
            case 2:
                if (front == -1) { // Check if the queue is empty
                    printf("Queue is empty\n");
                } else {
                    e = q[front];
                    printf("Element dequeued: %d\n", e);
                    if (front == rear) { // Queue becomes empty after dequeue
                        front = rear = -1;
                    } else {
                        front++;
                    }
                }
                break;
            case 3:
                if (front == -1) { // Check if the queue is empty
                    printf("Queue is empty\n");
                } else {
                    printf("Foremost value is: %d\n", q[front]);
                }
                break;
            case 4:
                if (front == -1) { // Check if the queue is empty
                    printf("Queue is empty\n");
                } else {
                    printf("Elements in the queue are: ");
                    for (int i = front; i <= rear; i++) {
                        printf("%d\t", q[i]);
                    }
                    printf("\n");
                }
                break;
            default:
                printf("Invalid option\n");
        }
        printf("Enter any number to continue and 0 for exit: ");
        scanf("%d", &c); // Read the input for continuing or exiting
    } while (c != 0);
    
    return 0; // Return 0 to indicate successful completion
}