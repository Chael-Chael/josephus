#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BCTree {
    int serial; // 序号
    int code;   // 密码
    int count;  // 计数  
    struct BCTree* L;
    struct BCTree* R;
    struct BCTree* P;
} TNode;

void showNode(TNode* node){
    printf("Node: %d\n", node->serial);
    printf("Code: %d\n", node->code);
    printf("Steps: %d\n", node->count);
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

}

void showTree(TNode* node) {
    if (node == NULL) {
        return;
    }
    
    printf("Node: %d\n", node->serial);
    printf("Code: %d\n", node->code);
    printf("Steps: %d\n", node->count);
    
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
        Mid->code = rand() % (3*high) + 1;
        Mid->count = high - low + 1;
        Mid->L = CreateTree(low, mid - 1, Mid);
        Mid->R = CreateTree(mid + 1, high, Mid);
        Mid->P = Parent;
        return Mid;
    } else {
        return NULL;
    }       
}

TNode* make_steps(TNode* CurrentNode, int count) {
    int rightsteps = 0;
    int leftsteps = 0;
    int rightLeftsteps = 0;
    int leftRightsteps = 0;

    if (count == 0) {
        return CurrentNode;    // find target
    }

    if (CurrentNode->R != NULL) {
        rightsteps = CurrentNode->R->count;
    }
    
    if (CurrentNode->L != NULL) {
        leftsteps = CurrentNode->L->count;
    }
    
    if (CurrentNode->R != NULL && CurrentNode->R->L != NULL) {
        rightLeftsteps = CurrentNode->R->L->count;
    }
    
    if (CurrentNode->L != NULL && CurrentNode->L->R != NULL) {
        leftRightsteps = CurrentNode->L->R->count;
    }
    
    if (0 < count && count <= rightsteps) {
        CurrentNode = CurrentNode->R;
        count = count - (rightLeftsteps + 1);
    } else if (-leftsteps <= count && count < 0) {
        CurrentNode = CurrentNode->L;
        count = count + (leftRightsteps + 1);
    } else {
        if (CurrentNode->P != NULL) {
            if (CurrentNode->P->L == CurrentNode) {
                CurrentNode = CurrentNode->P;
                count = count - (rightsteps + 1);
            } else {
                CurrentNode = CurrentNode->P;
                count = count + (leftsteps + 1);
            }
        } else {
            if (count > 0) {
                count = count - CurrentNode->count;
            } else if (count < 0) {
                count = count + CurrentNode->count;
            }
        }
    }
    return make_steps(CurrentNode, count);
}

TNode* delNodeAndGetNext(TNode* Node){
    TNode* parent = Node->P;
    TNode* left = Node->L;
    TNode* right = Node->R;
    TNode* temp;

    if (Node == NULL) {
        return NULL;
    }
    else if (Node->L == NULL && Node->R == NULL) {
        if (Node->P != NULL) {
            if (Node->P->L == Node) {
                Node->P->L = NULL;
            } else {
                Node->P->R = NULL;
            }
        }

        for (TNode* i = Node; i != NULL; i = i->P) {
            i->count--;
        }

        free(Node);
        Node = NULL;
        return parent;
    }
    else if (Node->L == NULL) {
        Node->R->P = Node->P;
        if (Node->P != NULL) {
            if (Node->P->L == Node) {
                Node->P->L = Node->R;
            } else {
                Node->P->R = Node->R;
            }
        }

        for (TNode* i = Node; i != NULL; i = i->P) {
            i->count--;
        }

        free(Node);
        Node = NULL;
        return right;
    }
    else if (Node->R == NULL) {
        Node->L->P = Node->P;
        if (Node->P != NULL) {
            if (Node->P->L == Node) {
                Node->P->L = Node->L;
            } else {
                Node->P->R = Node->L;
            }
        }

        for (TNode* i = Node; i != NULL; i = i->P) {
            i->count--;
        }

        free(Node);
        Node = NULL;
        return left;
    }
    else {
        TNode* NextNode = Node->R;
        while (NextNode->L != NULL) {
            NextNode = NextNode->L;
        }
        Node->serial = NextNode->serial;
        Node->code = NextNode->code;
        temp = delNodeAndGetNext(NextNode);

        while(!(temp->P == Node || temp == Node)){
            temp = temp->P;
        }

        Node->R = temp;
        return Node;
    }
}

void josephus(int n, int k, TNode* root){
    TNode* CurrentNode = root;
    TNode* NextNode;

    while(CurrentNode->L != NULL){
        CurrentNode = CurrentNode->L;
    }

    //printf("current node: %d\n", CurrentNode->serial); 
    int size = n;

    while(size > 1){
        printf("k = %d\n", k);
        k = (k - 1) % size;
        printf("k_next = %d\n", k);
        NextNode = make_steps(CurrentNode, k);
        printf("Person %d is out\n", NextNode->serial);

        k = NextNode->code;
        printf("nextnode = %d\n", NextNode->serial);
        if (NextNode->R == NULL && NextNode->L != NULL){
            k++;
            printf("yes...\n");
        }

        CurrentNode = delNodeAndGetNext(NextNode);
        printf("current node: %d\n", CurrentNode->serial);
        size --;

    }

    printf("The last person is %d\n", CurrentNode->serial);
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

        TNode* root = CreateTree(1, n, NULL);
        showTree(root);

        start = clock();
        josephus(n, k, root);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nProgram took %f seconds to execute \n", cpu_time_used);
        return 0;
    }
}