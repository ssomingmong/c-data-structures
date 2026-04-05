//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - 연결 리스트 문제
목적: 문제 3에서 요구하는 함수 구현 */

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
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	// 연결 리스트 1을 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;


	printf("1: 연결 리스트에 정수 삽입:\n");
	printf("2: 연결 리스트의 홀수 정수를 뒤로 이동:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("결과 연결 리스트: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // 이 함수를 직접 구현해야 합니다
			printf("홀수 정수를 뒤로 이동한 결과 연결 리스트: ");
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

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	if(ll -> head == NULL) return;  // 빈 리스트면 할 일 없음

	ListNode *cur = ll -> head;    // 현재 순회 중인 노드
	ListNode *prev = NULL;         // cur 바로 앞 노드 (홀수 분리 시 연결 끊을 때 필요)
	ListNode *odd_head = NULL;     // 홀수 노드 체인의 시작점
	ListNode *odd_tail = NULL;     // 홀수 노드 체인의 끝 (새 홀수 노드를 여기에 붙임)

	while(cur != NULL) {
		if(cur -> next -> item % 2 != 0) {  // 현재 노드가 홀수인 경우
			// 홀수 노드를 원래 자리에서 분리
			if(prev == NULL) {
				ll -> head = cur -> next;    // head가 홀수인 경우, head를 다음 노드로 변경
			}
			else prev -> next = cur -> next; // 중간 노드인 경우, 앞 노드가 다음 노드를 가리키게 함

			// 홀수 체인 끝에 분리한 노드 붙이기
			cur -> next = NULL;
			if(odd_head == NULL) {
				odd_head = odd_tail = cur;   // 홀수 체인이 비어있으면 첫 노드로 설정
			}
			else {
				odd_tail -> next = cur;      // 홀수 체인 끝에 연결
				odd_tail = cur;              // 홀수 체인 끝 포인터 이동
			}
		}
		else {
			prev = cur;  // 짝수 노드는 그대로 두고 prev만 이동
		}
		cur = cur -> next;  // 다음 노드로 이동
	}

	// 순회 완료 후 짝수 체인 끝에 홀수 체인 연결
	if(odd_head != NULL) {
		if(prev == NULL) {
			ll -> head = odd_head;     // 짝수 노드가 하나도 없는 경우
		}
		else prev -> next = odd_head;  // 짝수 체인의 마지막 노드 뒤에 홀수 체인 연결
	}
}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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
