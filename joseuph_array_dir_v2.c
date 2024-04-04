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
    if ( k > size / 2 )
    {
        dir = -1;
    }
    else if ( k  <= size / 2)
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
        if (k == 0){
            k = l->remaining;
        }//change k into steps, starting from the next node of the deleted value
        
        findDir(k, l->size);
        printf("dir = %d\n", dir);

        if (dir == -1){
            k = l->remaining + 2 - k;
        }

        printf("k = %d\n", k);
        
        while (count < k)
        {
            if (l->list[l->ptr].isOut == 0)
            {
                count++;
            }
            l->ptr = (l->ptr + dir + l->size) % l->size; //move to the next
            printf("ptr = %d\n", l->ptr);
        }

        printf("Person %d is out\n", (l->ptr - dir + l->size) % l->size + 1);
        sum -= (l->ptr - dir + l->size) % l->size + 1;
        l->remaining--;
        k = removeElem(l, (l->ptr - dir + l->size) % l->size);
        if( dir == -1){
            l->ptr = (l->ptr + 2) % l->size;
        }
        printf("ptr = %d\n", l->ptr);

    }

    printf("Last person standing is %d\n",sum);
}
