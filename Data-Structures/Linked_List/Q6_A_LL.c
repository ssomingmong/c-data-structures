//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - 연결 리스트 문제
목적: 문제 6에서 요구하는 함수 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// ListNode의 정의를 변경하지 마세요

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// LinkedList의 정의를 변경하지 마세요


//////////////////////// function prototypes /////////////////////////////////////

// 이 함수의 프로토타입을 변경하지 마세요
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	// 연결 리스트 1을 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;


	printf("1: 연결 리스트에 정수 삽입:\n");
	printf("2: 가장 큰 값을 리스트의 앞으로 이동:\n");
	printf("0: 종료:\n");

	while (c != 0)
	{
		printf("선택을 입력하세요(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("연결 리스트에 추가할 정수를 입력하세요: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("결과 연결 리스트: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // 이 함수를 직접 구현해야 합니다
			printf("가장 큰 값을 앞으로 이동한 결과 연결 리스트: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("알 수 없는 선택입니다;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
	ListNode *cur = *ptrHead;   // 순회용 포인터, 첫 번째 노드부터 시작
	ListNode *maxpre = NULL;    // 최댓값 노드의 이전 노드
	ListNode *max = *ptrHead;   // 최댓값 노드 (일단 head로 초기화)
	ListNode *pre = NULL;       // cur의 이전 노드

	if(*ptrHead == NULL) return 0;  // 빈 리스트면 종료

	// 리스트 전체 순회하며 최댓값 탐색
	while(cur != NULL) {
		if(cur -> item > max -> item) {
			max = cur;      // 최댓값 노드 갱신
			maxpre = pre;   // 최댓값의 이전 노드 갱신
		}
		pre = cur;
		cur = cur -> next;
	}

	// 최댓값이 이미 head이면 이동 불필요
	if(maxpre == NULL) return 1;

	maxpre -> next = max -> next;  // 최댓값 노드를 리스트에서 분리
	max -> next = *ptrHead;        // 최댓값 노드가 기존 head를 가리키게 함
	*ptrHead = max;                // head를 최댓값 노드로 변경

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////

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
