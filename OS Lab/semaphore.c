#include <stdio.h>

int mutex = 1;
int full = 0;
int empty;
int bufferSize;
int items = 0;

int wait(int *s) {
    return --(*s);
}

int signal(int *s) {
    return ++(*s);
}

void producer() {
    wait(&mutex);
    if (full == bufferSize) {
        printf("Buffer Full Condition Encountered\n"); 
        signal(&mutex);
        return;
    }
    wait(&empty);
    items++;
    printf("\nProduced item-%d, Total: %d", items, items);
    signal(&full);
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    if (empty == bufferSize) {
        printf("Buffer empty Condition Encountered\n"); 
        signal(&mutex);
        return;
    }
    wait(&full);
    int consumedItem = items; 
    items--;
    printf("\nConsumed item-%d, Total: %d", consumedItem, items); 
    signal(&empty);
    signal(&mutex);
}

int main() {
    printf("Buffer size: ");
    scanf("%d", &bufferSize);
    empty = bufferSize;

    int choice;
    do {
        printf("\n1) Produce 2) Consume 3) Exit: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                printf("exiting the code\n"); // Added newline for clarity
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}