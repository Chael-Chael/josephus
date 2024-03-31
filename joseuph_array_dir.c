#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Elem{
    int isOut;
    int code;
} Elem;

typedef struct List{
    Elem* list;
    int size;
    int remaining;
    int ptr;
} List;



void initList(List* l, int n);
void insert(List* l, int position, int code);
int removeElem(List *l, int position);
void josephus(int k, List *l);
void findDir(int k, int size);
void showList(int n, List* l);
int dir = 1;

int main() 
{
    int n ;
    int initialK ;
    List* l;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of initialK: ");
    scanf("%d", &initialK);

    if( n  <1 || initialK < 1 )
    {
        printf("Invalid input\n");
        return 0;
    }
    else
    {
    clock_t start, end;
    double cpu_time_used;

    initList(l, n);
    for (int i = 0; i < n; i++)
    {
        insert(l, i, rand() % 20 + 1);
    }
    showList(n, l);

    start = clock();
    josephus(initialK, l);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Program took %f seconds to execute \n", cpu_time_used);
    return 0;
    }
}

void initList(List* l, int n)
{
    l->list = (Elem*)malloc(sizeof(Elem)*(n));
    if (!l->list) 
    {
        printf("Memory error\n");
        return;
    }
    l->ptr = 0;
    l->size = n;
    l->remaining = n;
}

void insert(List* l, int position, int code)
{
    if (position < 0 || position > l->size - 1)
    {
        printf("Invalid insert position\n");
        return;
    }
    
    l->list[position].isOut = 0;
    l->list[position].code = code;
}

int removeElem(List* l, int position)
{
    if (position < 0 || position > l->size - 1)
    {
        printf("Invalid remove position\n");
        return 0;
    }
    
    int delElem = l->list[position].code;
    l->list[position].isOut = 1;
    l->list[position].code = 0;
    return delElem;
}

void findDir(int k, int size)
{
    if ( (k - 1) > size / 2 )
    {
        dir = -1;
    }
    else if ((k - 1) <= size / 2)
    {
        dir = 1;
    }   
} 

void showList(int n, List* l) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("Person %d has code %d\n", i + 1, l->list[i].code);
    }
}

void josephus(int k, List *l)
{
    int sum = l->size * (l->size + 1) / 2;
    while (l->remaining > 1 )
    {
        int count = 0;
        
        k = k % l-> remaining;
        if ( k == 0 ){
            k = l->remaining;
        }
        
        findDir(k, l->size);

        while (count < k)
        {
            if (l->list[l->ptr].isOut == 0)
            {
                count++;
            }
            l->ptr = (l->ptr + dir + l->size) % l->size; //move to the next
        }

        printf("Person %d is out\n", (l->ptr + l->size - 1) % l->size + 1);
        sum -= (l->ptr + l->size - 1) % l->size + 1;
        l->remaining--;
        k = removeElem(l, (l->ptr + l->size - 1) % l->size);
    }

    printf("Last person standing is %d\n",sum);
}

/*
typedef struct Queue{
    Elem* queue;
    int ptr;
    //int front;
    //int rear;
    int size;
} Queue;

typedef struct Elem{
    //int position;
    int isOut;
    int code;
} Elem;

void initQueue(Queue* q, int n);
void josephus(int n, int k, Queue *q);
void enqueue(Queue* q, int position, int code);
int dequeue(Queue* q);
int getQueueSize(Queue *q);

int main() 
{
    int n ;
    int initialK ;
    Queue* q;

    scanf("%d %d", &n, &initialK);
    if( n  <1 || initialK < 1 )
    {
        printf("Invalid input\n");
        return 0;
    }
    else
    {
    clock_t start, end;
    double cpu_time_used;

    initQueue(q, n);
    for (int i = 1; i <= n; i++)
    {
        enqueue(q, i, n);
    }

    start = clock();
    josephus(n, initialK, q);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Program took %f seconds to execute \n", cpu_time_used);
    return 0;
    }
}

void initQueue(Queue* q, int n)
{
    q->queue = (Elem*)malloc(sizeof(Elem)*(n));
    if (!q->queue) 
    {
        printf("Memory error\n");
        return;
    }
    // q->front = 0;
    // q->rear = 0;
    q->ptr = 0;
    q->size = n;
}

// int getQueueSize(Queue* q)
// {
//     return (q->rear - q->front + q->size) % q->size;
// }

void enqueue(Queue* q, int position, int code)
{
    if (q->ptr == q->size - 1)
    {
        printf("Queue is full\n");
        return;
    }
    
    q->ptr = position;
    q->queue[q->ptr].isOut = 0;
    q->queue[q->ptr].code = code;

    // (q->queue[q->rear]).position = positon;
    // (q->queue[q->rear]).code = code;
    // q->rear = (q->rear + 1) % q->size;
}

int dequeue(Queue* q)
{
    if (q->front == q->rear && (q->queue[q->front]).code == 0)
    {
        printf("Queue is empty\n");
        return 0;
    }
    int delElem = q->queue[q->front];
    q->front = (q->front + 1) % q->size;
    return delElem;
}

//逆时针
void josephus(int n, int k, Queue *q)
{
    while(n--){
        k = k % n; //预处理
        q->rear = q->rear + k - 1;
        printf("Person %d is out\n", q->rear + 1);
        enqueue(q, q->queue[(q->rear + 1) % n]);
        k = dequeue(q);
    }
    printf("Last person standing is %d\n", q->queue[q->front]);
}
*/ 