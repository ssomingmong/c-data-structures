//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - 이진 트리 문제
목적: 문제 2에서 요구하는 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // BTNode의 정의를 변경하지 마세요

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// 이 함수들의 프로토타입을 변경하지 마세요
int maxHeight(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c;
    char e;
	c = 1;

    BTNode *root;
    root = NULL;

    printf("1: 이진 트리 생성.\n");
    printf("2: 이진 트리의 최대 높이 찾기.\n");
    printf("0: 종료;\n");

    while(c != 0){
        printf("\n선택을 입력하세요(1/2/0): ");
        if(scanf("%d", &c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("결과 이진 트리: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                c = maxHeight(root);
                printf("이진 트리의 최대 높이: %d\n",c);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("알 수 없는 선택입니다;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int maxHeight(BTNode *node)

{
    /* 여기에 코드를 작성하세요 */
}

///////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("이진 트리에 추가할 정수를 입력하세요. 알파 값은 NULL로 처리됩니다.\n");
    printf("루트 노드의 정수 값을 입력하세요: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stk)) != NULL)
    {

        printf("%d의 왼쪽 자식 노드의 정수 값을 입력하세요: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("%d의 오른쪽 자식 노드의 정수 값을 입력하세요: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stk->top == NULL){
        stk->top = temp;
        temp->next = NULL;
    }
    else{
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;
   if(top != NULL){
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
   }
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
