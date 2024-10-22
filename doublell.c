#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* rlink;
     struct Node* llink;
} *I, *first = NULL, *last = NULL, *current, *prev = NULL;

int main()
{
    int ch, con, pos, item;
    do
    {   
        printf("Menu:\n1. Create LL\n2. Display forward\n3. Insertion at right\n4. Insertion at left\n5.  Deletion at Specified\n6. Deletion at first\n7. Deletion at last");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: 
                I = (struct Node*)malloc(sizeof(struct Node*));
                printf("Enter the data: ");
                scanf("%d", &item);
                I -> data = item;
                I -> rlink = NULL;
                 I -> llink = NULL;
                if(first == NULL)
                {
                    first = last = I;
                }else
                {
                    last -> rlink = I;
                    last -> llink = I;
                    last = I;
                }
                break;
                
            case 2: 
                current = first;
                if(first == NULL)
                {
                    printf("list is empty.");
                }
                else
                {
                    while(current->rlink!= NULL)
                    {
                    printf("%d\t", current -> data);
                    current = current -> rlink;
                    }
                }
                printf("\n");
                break;
                
            case 3: 
                I = (struct Node*)malloc(sizeof(struct Node*));
                printf("enter the data after which inserction is done");
                scanf("%d",&pos);
                printf("Enter the data: ");
                scanf("%d", &item);
                I -> data = item;
                I -> rlink = NULL;
                I -> llink = NULL;
                current=first;
                while(current->data!=pos)
                {
                current=current->rlink;
                I->llink=current;
                I->rlink=current->rlink;
                current->rlink->llink=I;
                current->rlink=I;
                }
                break;
                
            case 4: 
               I = (struct Node*)malloc(sizeof(struct Node*));
                printf("enter the data before which inserction is done");
                scanf("%d",&pos);
                printf("Enter the data: ");
                scanf("%d", &item);
                I -> data = item;
                I -> rlink = NULL;
                I -> llink = NULL;
                current=first;
                while(current->data!=pos)
                {
                current=current->rlink;
                I->rlink=current;
                I->llink=current->llink;
                current->llink->rlink=I;
                current->llink=I;
                }
                break;
                
            case 5: 
                I = (struct Node*)malloc(sizeof(struct Node*));
                printf("Enter item where u want to enter: ");
                scanf("%d", &pos);
                printf("Enter the data: ");
                scanf("%d", &item);
                I -> data = item;
                I -> llink = NULL;
                I -> rlink = NULL;
                current = first;
                while(current -> data != pos)   
                {
                    current = current -> rlink;
                    current->llink->rlink=current->rlink;
                    current->rlink->llink=current->llink;
                }
                break;
            
            case 6: 
                if(first == NULL)
                {
                    printf("Linked list is empty.\n");
                }
                else 
                {
                 first=first->rlink;
                 first->llink=NULL;
                }
                break;
            
            case 7: 
                if(first == NULL)
                {
                    printf("Linked list is empty.\n");
                }
                else last=last->llink;
                last->rlink=NULL;
                
            
                break;
        }
        printf("Enter 0 if u want to repeat again: ");
        scanf("%d", &con);
    }while(con==0);
}