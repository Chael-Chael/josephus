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
void josephus(int n, int k);
Node* josephus_recursion(int n, int k);

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
    return newNode;
}

void josephus(int n, int k) 
{
    Node *head = createNode(1, 1);
    Node *prev = head;
    for (int i = 2; i <= n; i++) 
    {
        prev->next = createNode(i, i);
        prev = prev->next;
    }
    
    prev->next = head;
    Node *ptr1 = head, *ptr2 = head;
    
    int remaining = n;
    int count = k;
    while (ptr1->next != ptr1) 
    {
        count = count % remaining;
        if (count == 0) 
        {
            count = remaining;
        }

        while (count-- != 1)
        {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
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