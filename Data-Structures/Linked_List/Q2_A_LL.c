//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - 연결 리스트 문제
목적: 문제 2에서 요구하는 함수 구현 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	// 연결 리스트 1을 빈 연결 리스트로 초기화
	ll1.head = NULL;
	ll1.size = 0;

	// 연결 리스트 2를 빈 연결 리스트로 초기화
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: 연결 리스트 1에 정수 삽입:\n");
	printf("2: 연결 리스트 2에 정수 삽입:\n");
	printf("3: 교대 병합 연결 리스트 생성:\n");
	printf("0: 종료:\n");

	while (c != 0)
	{
		printf("선택을 입력하세요(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("연결 리스트 1에 추가할 정수를 입력하세요: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("연결 리스트 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("연결 리스트 2에 추가할 정수를 입력하세요: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("연결 리스트 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("주어진 연결 리스트를 병합한 결과 연결 리스트:\n");
			alternateMergeLinkedList(&ll1, &ll2); // 이 함수를 직접 구현해야 합니다
			printf("결과 연결 리스트 1: ");
			printList(&ll1);
			printf("결과 연결 리스트 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("알 수 없는 선택입니다;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/*
 * ll1 = [1, 3, 5], ll2 = [2, 4, 6] 이면
 * 결과: ll1 = [1, 2, 3, 4, 5, 6], ll2 = [] (빈 리스트)
 *
 * ll2의 노드들을 ll1에 한 칸씩 끼워 넣는 방식으로 병합한다.
 * ll2가 ll1보다 길면 남은 ll2 노드들을 ll1 끝에 이어 붙인다.
 * ll1이 ll2보다 길면 ll1의 나머지 노드들은 그대로 유지된다.
 */
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	ListNode *cur1 = ll1 -> head;  // ll1 현재 노드
	ListNode *cur2 = ll2 -> head;  // ll2 현재 노드
	ListNode *next1, *next2;       // 다음 노드를 미리 저장 (포인터 변경 전에 백업)
	ListNode *last_cur2 = NULL;    // 루프에서 마지막으로 처리된 ll2 노드 (ll2 잔여 노드 연결에 사용)

	// ll1, ll2 모두 노드가 남아있는 동안 교대로 병합
	while (cur1 != NULL && cur2 != NULL){
		next1 = cur1 -> next;  // cur1의 원래 다음 노드 백업
		next2 = cur2 -> next;  // cur2의 원래 다음 노드 백업

		cur1 -> next = cur2;   // ll1 노드 뒤에 ll2 노드 연결: cur1 -> cur2
		cur2 -> next = next1;  // ll2 노드 뒤에 ll1의 다음 노드 연결: cur2 -> next1
		last_cur2 = cur2;      // 마지막으로 삽입된 ll2 노드 기록

		cur1 = next1;          // ll1 포인터를 다음 ll1 노드로 이동
		cur2 = next2;          // ll2 포인터를 다음 ll2 노드로 이동
	}

	// ll2가 ll1보다 길어서 남은 ll2 노드가 있는 경우, ll1 끝에 이어 붙임
	if (cur2 != NULL) {
		if (last_cur2 != NULL) {
			// 루프에서 마지막으로 처리된 ll2 노드 뒤에 나머지 ll2를 연결
			last_cur2 -> next = cur2;
		}
		else {
			// ll1이 처음부터 비어있었던 경우, ll2의 나머지를 ll1의 head로 설정
			ll1 -> head = cur2;
		}
	}

	// ll1의 size를 두 리스트의 합으로 갱신
	ll1->size = ll1->size + ll2->size;
	// ll2의 노드들은 이제 모두 ll1에 속하므로, ll2를 빈 리스트로 초기화
	// (초기화하지 않으면 removeAllItems 호출 시 이미 해제된 노드를 다시 해제해 double free 발생)
	ll2->head = NULL;
	ll2->size = 0;

	
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
