//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - 스택과 큐 문제
목적: 문제 1에서 요구하는 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

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


typedef struct _queue
{
	LinkedList ll;
} Queue;  // Queue의 정의를 변경하지 마세요

///////////////////////// function prototypes ////////////////////////////////////

// 이 함수들의 프로토타입을 변경하지 마세요
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// 연결 리스트를 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;

	// 큐를 빈 큐로 초기화
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: 연결 리스트에 정수 삽입:\n");
	printf("2: 연결 리스트로부터 큐 생성:\n");
	printf("3: 큐에서 홀수 제거:\n");
	printf("0: 종료:\n");


	while (c != 0)
	{
		printf("선택을 입력하세요(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("리스트에 삽입할 정수를 입력하세요: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("결과 연결 리스트: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // 이 함수를 직접 구현해야 합니다
			printf("결과 큐: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // 이 함수를 직접 구현해야 합니다
			printf("홀수를 제거한 결과 큐: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("알 수 없는 선택입니다;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	ListNode *cur = ll -> head;

	while(cur != NULL) {
		enqueue(q, cur -> item);
		cur = cur -> next;
	}
}

void removeOddValues(Queue *q)
{
	int size = q -> ll.size;

	for(int i = 0; i < size; i++) {
		int val = dequeue(q);
		if(val % 2 == 0) {
			enqueue(q, val);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
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
