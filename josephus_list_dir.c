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
void josephus(int n, int k, Node* head);
void createList(int n, Node* head);
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
    
    Node* head = createNode(1, rand() % n*3 + 1);
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
    newNode->prev = NULL;
    return newNode;
}

void findDir(int k, int size)
{
    if (k > (size-1) / 2 )
    {
        dir = -1;
    }
    else if (k <= (size-1) / 2)
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

void createList(int n, Node* head)
{
    Node* current = head;
    for (int i = 2; i <= n; i++) 
    {
        current->next = createNode(i, rand() % n*3 + 1);
        (current->next)->prev = current;
        current = current->next;
    }
    current->next = head;
    head->prev = current;
}

void josephus(int n, int k, Node* head) 
{
    Node *ptr1 = head, *ptr2 = head;
    
    int remaining = n;
    int count = k;
    while (ptr1->next != ptr1) 
    {
        count = (count - 1) % remaining;
        
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
            ptr2->next = ptr1->next;
            ptr2->next->prev = ptr2;
            free(ptr1);
            remaining--;
            ptr1 = ptr2->next;
        }
        else if(dir == -1){
            ptr2->prev = ptr1->prev;
            ptr2->prev->next = ptr2;
            free(ptr1);
            remaining--;
            ptr1 = ptr2;
            ptr2 = ptr1->prev;
        }
        //     ptr1 = ptr1->next;
        // } 
        // else if(dir == - 1){
        //     ptr1 = ptr1->prev;
        // }  
        
        // ptr2->prev = ptr1->prev;
        // ptr1 = ptr2->prev;
    }

    printf("Last person standing is %d\n", ptr1->data);
}