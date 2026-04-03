//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - 이진 탐색 트리 문제
목적: 문제 5에서 요구하는 함수 구현
		 BST의 '노드 삭제' 연산 구현 */
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // BSTNode의 정의를 변경하지 마세요

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // StackNode의 정의를 변경하지 마세요

typedef struct _stack
{
	StackNode *top;
}Stack; // Stack의 정의를 변경하지 마세요

///////////////////////// function prototypes ////////////////////////////////////

// 이 함수들의 프로토타입을 변경하지 마세요
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// 이진 탐색 트리를 빈 이진 탐색 트리로 초기화
	BSTNode * root;
	root = NULL;

	printf("1: 이진 탐색 트리에 정수 삽입;\n");
	printf("2: 이진 탐색 트리의 후위 순회 출력;\n");
	printf("0: 종료;\n");


	while (c != 0)
	{
		printf("선택을 입력하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("이진 탐색 트리에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("이진 탐색 트리의 후위 순회 결과: ");
			postOrderIterativeS2(root); // 이 함수를 직접 구현해야 합니다
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("알 수 없는 선택입니다;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	 /* 여기에 코드를 작성하세요 */
}

/* 이진 탐색 트리와 키를 받아 해당 키를 삭제하고 새로운 루트를 반환하는 함수. 재귀 함수로 작성하세요. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	/* 여기에 코드를 작성하세요 */
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
