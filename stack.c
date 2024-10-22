#include <stdio.h>

#define n 5
int stack[n];
int top=-1;

void push(){
    int ele;
    printf("Enter element for push: ");
    scanf("%d",&ele);
    if (top>=n-1){
        printf("overflow condition encountered ");
    }
    else{
        top++;
        stack[top]=ele;
        printf("element pushed successfully\n");
    }
}

void pop(){
    int element;
    if (top==-1){
        printf("underflow condition encountered ");
        printf("means stack is empty \n");
    }
    else {
        element=stack[top];
        top--;
        printf("element popped out is %d\n",element);
    }
}

void peek(){
    if (top==-1){
        printf("underflow condition [stack is empty]\n");
    }
    else{
        printf("topmost element of stack ::%d\n",stack[top]);
    }
}

void display(){
    if (top==-1){
        printf("no elements in stack underflow\n");
    }
    else{
        int i;
        printf("elements of stack are::::::\n");
        for (i=top;i>=0;i--){
            printf("%d ",stack[i]);
        }
        printf("\n");
    }
}

int main(){
    int e;
    int choice;
    do {
        printf("1:  push\n");
    printf("2: pop\n");
    printf("3: peek\n");
    printf("4: display\n");
    printf("other number: exit\n");
    printf("enter your choice: ");
    scanf("%d",&e);
       switch(e){
        case 1: push();
        break;
        case 2: pop();
        break;
        case 3: peek();
        break;
        case 4: display();
        break;
        default : printf("Enter valid choice \n");
    }
    printf("Enter your choice for continuation [1 for yes and 0 for no]: ");
    scanf("%d",&choice);
    }
    while(choice==1);
    return 0;
}