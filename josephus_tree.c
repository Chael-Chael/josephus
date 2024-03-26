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


TNode *CreateTree( int low, int high,TNode* Parent){
    if(low <= high){
        int mid = (low + high) / 2;
        TNode* Mid = (TNode*) malloc (sizeof(TNode);
        Mid -> data = mid;
        Mid -> count = high - low + 1;
        Mid -> L = CreateTree(low, mid - 1, Mid);
        Mid -> R = CreateTree(mid + 1, high, Mid);
        Mid -> P = Parent;
        return Mid;
    }
    else{
        return NULL;
    }       
}

TNode *search( TNode *Tree, int count){
    if ( k == 0 ){
        return Tree;    //find target
    }
    
    int rightCount = (Tree->R)->count;
    int leftCount = (Tree->L)->count;
    int rightLeftCount = ((Tree->R)->L)->count;
    int leftRightCount = ((Tree->L)->R)->count;
    
    if ( 0 < k && k <= rightCount)
    {
        Tree = Tree->R;
        k = k - (rightLeftCount + 1);
    }
    else{
        if( Tree->P != NULL){
            if ( (Tree->P)->L == Tree ){
                Tree = Tree->P;
                count = count - (rightCount + 1);
            }
            else{
                Tree = Tree->P;
                count = count + (leftCount + 1);
            }
        }
        else{
            if (count > 0){
                count = count - Tree->count;
            }
            else if (count < 0){
                count = count + Tree->count;
            }
        }
    }            
    return search(Tree, count);
}

TNode *deleteNode( TNode *Tree ){
}

int josephus(int n, int k){
    int* list = (int*)malloc(sizeof(int) * n);
    TNode* root = CreateTree(1, n, NULL);
    TNode* Tree = root;
    
    for(int