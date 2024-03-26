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

int dir = 1;

int main() 
{
    int n ;
    int k ;
    scanf("%d %d", &n, &k);
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

void josephus(int n, int k) 
{
    Node *head = createNode(1, 1);
    Node *current = head;
    for (int i = 2; i <= n; i++) 
    {
        current->next = createNode(i, i);
        (current->next)->prev = current;
        current = current->next;
    }
    current->next = head;
    head->prev = current;
    
    Node *ptr1 = head, *ptr2 = head;
    
    int remaining = n;
    int count = k;
    while (ptr1->next != ptr1) 
    {
        count = count % remaining;
        if ( count == 0 )
        {
            count == remaining;
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
        
        if(dir == 1){
            ptr1 = ptr1->next;
        } 
        else if(dir == - 1){
            ptr1 = ptr1->prev;
        }  
        
        ptr2->prev = ptr1->prev;
        free(ptr1); 
        remaining--;
        ptr1 = ptr2->prev;
    }

    printf("Last person standing is %d\n", ptr1->data);
}

Node* josephus_recursion (int n, int k)
{
    if (n == 1)
    {
        printf("Last person standing is %d\n", person->data);
        return;
    }
    else
    {
        int serial = (josephus_recursion(n - 1, k) + k - 1) % n + 1;
        printf("Person %d is out\n", person->data);
        return person;
    }
}