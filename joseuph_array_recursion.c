#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue{
    int* queue;
    int front;
    int rear;
    int size;
} Queue;



void initQueue(Queue* q, int n);
int josephus(int n, int k, Queue *q);
void enqueue(Queue* q, int data);
int dequeue(Queue* q, int delElem);
int getQueueSize(Queue *q);

int main() 
{
    int n ;
    int initialK ;
    Queue* q;

    scanf("%d %d", &n, &initialK);
    if(n<1 || initialK<1)
    {
        printf("Invalid input\n");
        return 0;
    }
    else
    {
    clock_t start, end;
    double cpu_time_used;

    initQueue(q, n + 1);
    for (int i = 1; i <= n; i++)
    {
        enqueue(q, i);
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
    q->queue = (int*)malloc(sizeof(int)*(n + 1));
    if (!q->queue) 
    {
        printf("Memory error\n");
        return;
    }

    q->front = 0;
    q->rear = 0;
    q->size = n + 1;
}

int getQueueSize(Queue* q)
{
    return (q->rear - q->front + q->size) % q->size;
}

void enqueue(Queue* q, int data)
{
    if (getQueueSize(q) == q->size - 1)
    {
        printf("Queue is full\n");
        return;
    }

    q->queue[q->rear] = data;
    q->rear = (q->rear + 1) % q->size;
}

int dequeue(Queue* q, int delElem)
{
    if (getQueueSize(q) == 0)
    {
        printf("Queue is empty\n");
        return;
    }
    delElem = q->queue[q->front];
    q->front = (q->front + 1) % q->size;
    return delElem;
}

//逆时针
int josephus(int n, int k, Queue *q)
{
    if (n == 1)
    {
        return 0;
    }
    else
    {
        int ThisK = k % n; //预处理
        
        int nextK = dequeue(q, ThisK);
        enqueue(q, nextK);
        
        int PersonOut = (josephus(n - 1, nextK, q) + ThisK) % n;
        printf("Person %d is out\n", PersonOut + 1);
        return 
    }
}
