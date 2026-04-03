
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - 이진 탐색 트리 문제
목적: 문제 1에서 요구하는 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // BSTNode의 정의를 변경하지 마세요

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // QueueNode의 정의를 변경하지 마세요


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // queue의 정의를 변경하지 마세요

///////////////////////////////////////////////////////////////////////////////////

// 이 함수들의 프로토타입을 변경하지 마세요
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// 이진 탐색 트리를 빈 이진 탐색 트리로 초기화
	BSTNode *root;
	root = NULL;

	printf("1: 이진 탐색 트리에 정수 삽입;\n");
	printf("2: 이진 탐색 트리의 레벨 순서 순회 출력;\n");
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
			printf("이진 탐색 트리의 레벨 순서 순회 결과: ");
			levelOrderTraversal(root); // 이 함수를 직접 구현해야 합니다
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

void levelOrderTraversal(BSTNode* root)
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

// 노드를 큐에 삽입
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// 동적 메모리 할당
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// newPtr이 NULL이 아닌 경우
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// 큐가 비어있으면 head에 삽입
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // tail에 삽입
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("노드가 삽입되지 않았습니다");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
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
