//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - 스택과 큐 문제
목적: 문제 7에서 요구하는 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// ListNode의 정의를 변경하지 마세요

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// LinkedList의 정의를 변경하지 마세요


typedef struct stack
{
	LinkedList ll;
} Stack; // stack의 정의를 변경하지 마세요

///////////////////////// function prototypes ////////////////////////////////////

// 이 함수들의 프로토타입을 변경하지 마세요
int balanced(char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// 연결 리스트를 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;

	// 스택을 빈 스택으로 초기화
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: 문자열 입력:\n");
	printf("2: ()[]{} 문자로 구성된 표현식의 균형 여부 확인:\n");
	printf("0: 종료:\n");


	while (c != 0)
	{
		printf("선택을 입력하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("균형 여부를 확인할 표현식을 공백 없이 입력하세요: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(str))
                printf("균형이 맞지 않습니다!\n");
            else
                printf("균형이 맞습니다!\n");
			break;
		case 0:
			break;
		default:
			printf("알 수 없는 선택입니다;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
/* 여기에 코드를 작성하세요 */
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;

	cur = ll->head;
	if (cur == NULL)
		printf("비어있음");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 첫 번째 노드 삽입 시, head 포인터 업데이트 필요
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// 목표 위치의 이전 노드와 현재 노드 찾기
	// 새 노드를 만들고 링크 재연결
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 삭제 가능한 최대 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드 삭제 시, head 포인터 업데이트 필요
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// 목표 위치의 이전 노드와 다음 노드 찾기
	// 목표 노드를 해제하고 링크 재연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
