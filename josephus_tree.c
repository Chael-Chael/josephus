#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BCTree{
    int data;
    int code;
    int serial;
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
    if ( count == 0 ){
        return Tree;    //find target
    }
    
    int rightCount = (Tree->R)->count;
    int leftCount = (Tree->L)->count;
    int rightLeftCount = ((Tree->R)->L)->count;
    int leftRightCount = ((Tree->L)->R)->count;
    
    if ( 0 < count && count <= rightCount)
    {
        Tree = Tree->R;
        count = count - (rightLeftCount + 1);
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
    TNode *Parent = Tree->P;
    TNode *Left = Tree->L;
    TNode *Right = Tree->R;
    
    if (Left == NULL && Right == NULL){
        if (Parent->L == Tree){
            Parent->L = NULL;
        }
        else{
            Parent->R = NULL;
        }
        free(Tree);
        return Parent;
    }
    else if (Left == NULL){
        if (Parent->L == Tree){
            Parent->L = Right;
        }
        else{
            Parent->R = Right;
        }
        Right->P = Parent;
        free(Tree);
        return Right;
    }
    else if (Right == NULL){
        if (Parent->L == Tree){
            Parent->L = Left;
        }
        else{
            Parent->R = Left;
        }
        Left->P = Parent;
        free(Tree);
        return Left;
    }
    else{
        TNode *Temp = Right;
        while (Temp->L != NULL){
            Temp = Temp->L;
        }
        Tree->data = Temp->data;
        Tree->code = Temp->code;
        Tree->serial = Temp->serial;
        Tree->R = deleteNode(Temp);
        return Tree;
    }
}

int josephus(int n, int k){
    int* list = (int*)malloc(sizeof(int) * n);
    TNode* root = CreateTree(1, n, NULL);
    TNode* Tree = root;
    
    for(int size = n; size > 1; size ++){
        k = (k - 1) % size;
        Tree = search(Tree, k);
        printf("Person %d is out", Tree->serial);
        k = Tree->code;
        Tree = deleteNode(Tree); 
    }
    
    printf("Last person standing is %d", Tree->data);