#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    int code;
    struct Node* next;
    struct Node* prev;
} Node;

// typedef struct List{
//     Node* head;
//     Node* tail;
//     int length;
// } List;

Node* createNode(int data, int code);
void josephus(int n, int k);
Node* josephus_recursion(int n, int k);
void findDir(int k, int size);
void showList(int n, Node* head);

int dir = 1;

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
    start = clock();
    josephus(n, k);
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
    newNode->prev = NULL;
    return newNode;
}

void findDir(int k, int size)
{
    if ((k - 1) > size / 2 )
    {
        dir = -1;
    }
    else if ((k - 1) <= size / 2)
    {
        dir = 1;
    }   
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

void josephus(int n, int k) 
{
    Node *head = createNode(1, rand() % 20 + 1);
    Node *current = head;
    for (int i = 2; i <= n; i++) 
    {
        current->next = createNode(i, rand() % 20 + 1);
        (current->next)->prev = current;
        current = current->next;
    }
    current->next = head;
    head->prev = current;
    showList(n, head);
    
    Node *ptr1 = head, *ptr2 = head;
    
    int remaining = n;
    int count = k;
    while (ptr1->next != ptr1) 
    {
        count = count % remaining;
        if ( count == 0 )
        {
            count = remaining - 1;
        }
        else
        {
            count = count - 1;
        }
        
        findDir(count, remaining);

        while (count != 0)
        {
            ptr2 = ptr1;
            if(dir == 1){
                ptr1 = ptr1->next;
            } 
            else if(dir == - 1){
                ptr1 = ptr1-> prev;
            }   
            count --;
        } 

        printf("Person %d is out\n", ptr1->data);  
        count = ptr1->code;
        
        // if(dir == 1){
        //     ptr1 = ptr1->next;
        // } 
        // else if(dir == - 1){
        //     ptr1 = ptr1->prev;
        // }  
        
        // ptr2->prev = ptr1->prev;
        ptr2->next = ptr1->next;
        free(ptr1); 
        remaining--;
        ptr1 = ptr2->next;
        // ptr1 = ptr2->prev;
    }

    printf("Last person standing is %d\n", ptr1->data);
}