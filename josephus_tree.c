#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BCTree {
    int serial; // 序号
    int code;   // 密码
    int steps;  // 计数  
    struct BCTree* L;
    struct BCTree* R;
    struct BCTree* P;
} TNode;

void showTree(TNode* node) {
    if (node == NULL) {
        return;
    }
    
    printf("Node: %d\n", node->serial);
    printf("Code: %d\n", node->code);
    printf("Steps: %d\n", node->steps);
    
    if (node->L != NULL) {
        printf("Left Child: %d\n", node->L->serial);
    } else {
        printf("Left Child: NULL\n");
    }
    
    if (node->R != NULL) {
        printf("Right Child: %d\n", node->R->serial);
    } else {
        printf("Right Child: NULL\n");
    }
    
    if (node->P != NULL) {
        printf("Parent: %d\n", node->P->serial);
    } else {
        printf("Parent: NULL\n");
    }
    
    printf("\n");
    
    showTree(node->L);
    showTree(node->R);
}

TNode* CreateTree(int low, int high, TNode* Parent) {
    if (low <= high) {
        int mid = (low + high) / 2;
        TNode* Mid = (TNode*)malloc(sizeof(TNode));
        Mid->serial = mid;
        Mid->code = rand() % 20 + 1;
        Mid->steps = high - low + 1;
        Mid->L = CreateTree(low, mid - 1, Mid);
        Mid->R = CreateTree(mid + 1, high, Mid);
        Mid->P = Parent;
        return Mid;
    } else {
        return NULL;
    }       
}

TNode* step(TNode* TreeNode, int steps) {
    if (steps == 0) {
        return TreeNode;    // find target
    }
    
    int rightsteps = 0;
    int leftsteps = 0;
    int rightLeftsteps = 0;
    int leftRightsteps = 0;
    
    if (TreeNode->R != NULL) {
        rightsteps = TreeNode->R->steps;
    }
    
    if (TreeNode->L != NULL) {
        leftsteps = TreeNode->L->steps;
    }
    
    if (TreeNode->R != NULL && TreeNode->R->L != NULL) {
        rightLeftsteps = TreeNode->R->L->steps;
    }
    
    if (TreeNode->L != NULL && TreeNode->L->R != NULL) {
        leftRightsteps = TreeNode->L->R->steps;
    }
    
    if (0 < steps && steps <= rightsteps) {
        TreeNode = TreeNode->R;
        steps = steps - (rightLeftsteps + 1);
    } else if (-leftsteps <= steps && steps < 0) {
        TreeNode = TreeNode->L;
        steps = steps + (leftRightsteps + 1);
    } else {
        if (TreeNode->P != NULL) {
            if (TreeNode->P->L == TreeNode) {
                TreeNode = TreeNode->P;
                steps = steps - (rightsteps + 1);
            } else {
                TreeNode = TreeNode->P;
                steps = steps + (leftsteps + 1);
            }
        } else {
            if (steps > 0) {
                steps = steps - TreeNode->steps;
            } else if (steps < 0) {
                steps = steps + TreeNode->steps;
            }
        }
    }
    
    return step(TreeNode, steps);
}

void *deleteNode( TNode *TreeNode ){
    TNode *Parent = TreeNode->P;
    TNode *Left = TreeNode->L;
    TNode *Right = TreeNode->R;
    TNode *Temp;


    if (Left == NULL && Right == NULL){

        TNode *currentNode = TreeNode;
        while (currentNode->P != NULL) {
            currentNode = currentNode->P;
            currentNode->steps--;
        }

        if (Parent->L == TreeNode){
            Parent->L = NULL;
        }
        else{
            Parent->R = NULL;
        }
        free(TreeNode);
        TreeNode = NULL;
    }
    else if (Left == NULL){
        
        TNode *currentNode = TreeNode;
        while (currentNode->P != NULL) {
            currentNode = currentNode->P;
            currentNode->steps--;
        }

        if (Parent->L == TreeNode){
            Parent->L = Right;
        }
        else{
            Parent->R = Right;
        }
        Right->P = Parent;
        free(TreeNode);
        TreeNode = NULL;
    }
    else if (Right == NULL){

        TNode *currentNode = TreeNode;
        while (currentNode->P != NULL) {
            currentNode = currentNode->P;
            currentNode->steps--;
        }

        if (Parent->L == TreeNode){
            Parent->L = Left;
        }
        else{
            Parent->R = Left;
        }
        Left->P = Parent;
        free(TreeNode);
        TreeNode = NULL;
    }
    else{
        TNode *temp2 = Right;
        while (temp2->L != NULL){
            temp2 = temp2->L;
        }

        TNode *currentNode = temp2;
        while (currentNode->P != NULL) {
            currentNode = currentNode->P;
            currentNode->steps--;
        }
        
        TreeNode->code = temp2->code;
        TreeNode->serial = temp2->serial;

        if (temp2->P->L == temp2){
            temp2->P->L = temp2->R;
        }
        else{
            temp2->P->R = temp2->R;
        }

        free(temp2);
        temp2 = NULL;
    }
}

int josephus(int n, int k){
    int* list = (int*)malloc(sizeof(int) * n);
    TNode* root = CreateTree(1, n, NULL);
    TNode* TreeNode;
    TNode* FirstNode;
    TNode* NextTNode;

    showTree(root);

    k = k % n - (1 + n) / 2;
    FirstNode= step(root, k);
    printf("Person %d is out\n", FirstNode->serial);
    k = FirstNode->code;
    TreeNode = FirstNode;
    deleteNode(FirstNode);

    for(int size = n - 1; size > 1; size --){
        k = k % size;
        if (k == 0){
            k = size;
        }
        else {
            k =  k;
        }
        NextTNode = step(TreeNode, k);
        deleteNode(TreeNode);
        printf("Person %d is out\n", NextTNode->serial);
        k = NextTNode->code;
        TreeNode = NextTNode;
        printf("Remaining %d people\n", size - 1);
    }
    
    printf("Last person standing is %d", TreeNode->serial);
}

int main(){
    int n, k;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of k: ");
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
        start = clock();
        josephus(n, k);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nProgram took %f seconds to execute \n", cpu_time_used);
        return 0;
    }
}