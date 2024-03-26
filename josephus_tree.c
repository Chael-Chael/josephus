#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BCTree{
    int code;
    int count;
    struct BCTree *L;
    struct BCTree *R;
    struct BCTree *P;
} TNode;


TNode *Create 
    