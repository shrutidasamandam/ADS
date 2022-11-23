#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *npx;
};

struct node *XOR(struct node *a, struct node *b)
{
    return (struct node*)((unsigned int)(a)^(unsigned int)(b));
}

/*void insert(struct node **head_ref, int data)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->npx = XOR(*head_ref,NULL);
    if(*head_ref!=NULL)
    {
        struct node *next = XOR((*head_ref)->npx, NULL);
        (*head_ref)->npx = XOR(new_node,next);
    }
    *head_ref = new_node;
}
*/

struct node* insert(struct Node** head,int value,int position)
{
    if (*head == NULL) {
        if (position == 1) {
            struct node* Node = (struct Node*)malloc(sizeof(struct node));
            Node->data = value;
            Node->npx = XOR(NULL, NULL);
            *head = Node;
        }
        else {
            printf("Invalid Position\n");
        }
    }
    else {
        int Pos = 1;
        struct node* curr = *head;
        struct node* prev = NULL;
        struct node* next = XOR(prev, curr->npx);
        while (next != NULL && Pos < position - 1) {
            prev = curr;
            curr = next;
            next = XOR(prev, curr->npx);
            Pos++;
        }
        if (Pos == position - 1) {
            struct node* Node = (struct node*)malloc(sizeof(struct node));
            struct node* temp = XOR(curr->npx, next);
            curr->npx = XOR(temp, Node);
            if (next != NULL) {
                next->npx = XOR(Node,
                                XOR(next->npx, curr));
            }
            Node->npx = XOR(curr, next);
            Node->data = value;
        } else if (position == 1) {
            struct node* Node
                = (struct node*)malloc(
                    sizeof(struct node));
            curr->npx = XOR(Node, XOR(NULL, curr->npx));
            Node->npx = XOR(NULL, curr);
            *head = Node;
            Node->data = value;
        }
        else {
            printf("Invalid Position\n");
        }
    }
    return *head;
}


struct Node *del(struct Node** head)
{
    if (*head == NULL)
        printf("List is empty");
    else {
        struct node* curr = *head;
        struct node* prev = NULL;
        struct node* next;
        while (XOR(curr->npx, prev) != NULL) {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        if (prev != NULL)
            prev->npx = XOR(XOR(prev->npx, curr), NULL);
        else
            *head = NULL;
        free(curr);
    }
    return *head;
}

void printList(struct node *head){
    struct node *curr = head;
    struct node *prev = NULL;
    struct node *next;

    printf("Following are the nodes of Linked List: \n");

    while(curr!=NULL)
    {
        printf("%d ",curr->
        data);
        next = XOR(prev,curr->npx);
        prev = curr;
        curr = next;
    }
}

int main() {
   
    struct node *head = NULL;
    int ch;
    int value,pos;
    while(1)
    {
        printf("\n1.Insert a Node \n2. Print the List of Nodes \n3.Delete \n4.Exit");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            printf("\nEnter data value");
            scanf("%d",&value);
             printf("\nEnter position");
            scanf("%d",&pos);
            insert(&head, value, pos);
            break;
            case 2:
            printList(head);
            break;
            case 3: 
            del(&head);
            printList(head);
            break;
            case 4:
            exit(0);
            break;
        }
    }
 
    return (0);
}

