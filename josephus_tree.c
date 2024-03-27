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

TNode *search( TNode *TreeNode, int count){
    if ( count == 0 ){
        return TreeNode;    //find target
    }
    
    int rightCount = (TreeNode->R)->count;
    int leftCount = (TreeNode->L)->count;
    int rightLeftCount = ((TreeNode->R)->L)->count;
    int leftRightCount = ((TreeNode->L)->R)->count;
    
    if ( 0 < count && count <= rightCount)
    {
        TreeNode = TreeNode->R;
        count = count - (rightLeftCount + 1);
    }
    else{
        if( TreeNode->P != NULL){
            if ( (TreeNode->P)->L == TreeNode ){
                TreeNode = TreeNode->P;
                count = count - (rightCount + 1);
            }
            else{
                TreeNode = TreeNode->P;
                count = count + (leftCount + 1);
            }
        }
        else{
            if (count > 0){
                count = count - TreeNode->count;
            }
            else if (count < 0){
                count = count + TreeNode->count;
            }
        }
    }            
    return search(TreeNode, count);
}

TNode *deleteNode( TNode *TreeNode){
    TNode *Parent = TreeNode->P;
    TNode *Left = TreeNode->L;
    TNode *Right = TreeNode->R;
    
    if (Left == NULL && Right == NULL){
        if (Parent->L == TreeNode){
            Parent->L = NULL;
        }
        else{
            Parent->R = NULL;
        }
        free(TreeNode);
        return Parent;
    }
    else if (Left == NULL){
        if (Parent->L == TreeNode){
            Parent->L = Right;
        }
        else{
            Parent->R = Right;
        }
        Right->P = Parent;
        free(TreeNode);
        return Right;
    }
    else if (Right == NULL){
        if (Parent->L == TreeNode){
            Parent->L = Left;
        }
        else{
            Parent->R = Left;
        }
        Left->P = Parent;
        free(TreeNode);
        return Left;
    }
    else{
        TNode *Temp = Right;
        while (Temp->L != NULL){
            Temp = Temp->L;
        }
        TreeNode->data = Temp->data;
        TreeNode->code = Temp->code;
        TreeNode->serial = Temp->serial;
        TreeNode->R = deleteNode(Temp);
        return TreeNode;
    }
}

int josephus(int n, int k){
    int* list = (int*)malloc(sizeof(int) * n);
    TNode* root = CreateTree(1, n, NULL);
    TNode* TreeNode = root;
    
    for(int size = n; size > 1; size ++){
        k = (k - 1) % size;
        TreeNode = search(TreeNode, k);
        printf("Person %d is out", TreeNode->serial);
        k = TreeNode->code;
        TreeNode = deleteNode(TreeNode); 
    }
    
    printf("Last person standing is %d", TreeNode->data);