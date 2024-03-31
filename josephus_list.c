#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    int code;
    struct Node* next;
} Node;

// typedef struct List{
//     Node* head;
//     Node* tail;
//     int length;
// } List;

Node* createNode(int data, int code);
void josephus(int n, int k, Node* head);
void createList(int n, Node* head);
void showList(int n, Node* head);

int main() 
{
    int n ;
    int k ;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of initialK: ");
    scanf("%d", &k);

    if(n<1 || k<1)
    {
        printf("Invalid input\n");
        return 0;
    }
    else
    {
    clock_t start, end;
    double cpu_time_used;

    Node* head = createNode(1, rand() % 20 + 1);
    createList(n, head);
    showList(n, head);

    start = clock();
    josephus(n, k, head);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Program took %f seconds to execute \n", cpu_time_used);
    return 0;
    }
}

Node* createNode(int data, int code) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) 
    {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->code = code;
    newNode->next = NULL;
    return newNode;
}

void showList(int n, Node* head) 
{
    Node* ptr = head;
    for (int i = 0; i < n; i++) 
    {
        printf("Person %d has code %d\n", ptr->data, ptr->code);
        ptr = ptr->next;
    }
}

void createList(int n, Node* head) 
{
    Node* prev = head;
    for (int i = 2; i <= n; i++) 
    {
        prev->next = createNode(i, rand() % 20 + 1);
        prev = prev->next;
    }
    prev->next = head;
}

void josephus(int n, int k, Node* head) 
{
    Node *ptr1 = head, *ptr2 = head;
    
    int remaining = n;
    int count = k;
    while (ptr1->next != ptr1) 
    {
        count = count % remaining;
        if ( count  == 0 )
        {
            count = remaining - 1;
        } 
        else
        {
            count = count - 1;
        }

        while (count != 0)
        {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            count --;
        } 

        printf("Person %d is out\n", ptr1->data);  
        count = ptr1->code;

        ptr2->next = ptr1->next;
        free(ptr1); 
        remaining--;
        ptr1 = ptr2->next;
    }

    printf("Last person standing is %d\n", ptr1->data);
}