# 자료구조 - 연결 리스트 문제 풀이 (Q1 ~ Q7)

## 연결 리스트 구조

```c
typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;
```

---

## Q1. 정렬된 연결 리스트에 삽입 `insertSortedLL`

### 문제
정렬된 연결 리스트에 새로운 값을 올바른 위치에 삽입한다.

### 풀이
```c
int insertSortedLL(LinkedList *ll, int item)
{
    ListNode *newNode;
    ListNode *cur;

    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        return 0;

    newNode->item = item;
    newNode->next = NULL;

    // 빈 리스트이거나 head보다 작으면 앞에 삽입
    if (ll->head == NULL || item <= ll->head->item) {
        newNode->next = ll->head;
        ll->head = newNode;
        ll->size++;
        return 1;
    }

    // 삽입 위치 탐색
    cur = ll->head;
    while (cur->next != NULL && cur->next->item < item) {
        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
    ll->size++;

    return 1;
}
```

### 핵심 포인트
- `cur->next->item < item` 조건으로 삽입 위치 탐색
- head 앞에 삽입하는 경우를 먼저 처리

---

## Q2. 두 연결 리스트 교대 병합 `alternateMergeLinkedList`

### 문제
두 연결 리스트를 교대로 병합한다.
- `ll1 = [1, 3, 5]`, `ll2 = [2, 4, 6]` → `ll1 = [1, 2, 3, 4, 5, 6]`

### 풀이
```c
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    ListNode *cur1 = ll1->head;
    ListNode *cur2 = ll2->head;
    ListNode *next1, *next2;
    ListNode *last_cur2 = NULL;

    while (cur1 != NULL && cur2 != NULL) {
        next1 = cur1->next;
        next2 = cur2->next;

        cur1->next = cur2;   // ll1 노드 뒤에 ll2 노드 연결
        cur2->next = next1;  // ll2 노드 뒤에 ll1의 다음 노드 연결

        last_cur2 = cur2;
        cur1 = next1;
        cur2 = next2;
    }

    // ll2가 더 길면 남은 노드 이어 붙이기
    if (cur2 != NULL && last_cur2 != NULL)
        last_cur2->next = cur2;

    ll1->size += ll2->size;
    ll2->head = NULL;
    ll2->size = 0;
}
```

### 핵심 포인트
- 포인터를 변경하기 전에 `next1`, `next2`에 미리 백업
- ll2가 더 길면 남은 노드를 ll1 끝에 이어 붙임

---

## Q3. 홀수 값을 뒤로 이동 `moveOddItemsToBack`

### 문제
연결 리스트에서 홀수 값을 가진 노드를 모두 뒤로 이동한다.
- `[1, 2, 3, 4, 5]` → `[2, 4, 1, 3, 5]`

### 풀이
```c
void moveOddItemsToBack(LinkedList *ll)
{
    if (ll->head == NULL) return;

    ListNode *cur = ll->head;
    ListNode *prev = NULL;
    ListNode *odd_head = NULL;
    ListNode *odd_tail = NULL;

    while (cur != NULL) {
        ListNode *next = cur->next;

        if (cur->item % 2 != 0) {
            // 홀수 노드를 리스트에서 분리
            if (prev == NULL)
                ll->head = next;
            else
                prev->next = next;

            cur->next = NULL;

            // 홀수 리스트에 추가
            if (odd_head == NULL)
                odd_head = odd_tail = cur;
            else {
                odd_tail->next = cur;
                odd_tail = cur;
            }
        } else {
            prev = cur;
        }
        cur = next;
    }

    // 홀수 리스트를 원본 리스트 끝에 붙이기
    if (odd_head != NULL) {
        if (prev == NULL)
            ll->head = odd_head;
        else
            prev->next = odd_head;
    }
}
```

### 핵심 포인트
- 홀수 노드만 따로 모아 `odd_head ~ odd_tail` 리스트 구성
- 순회 후 원본 리스트 끝에 이어 붙임

---

## Q4. 짝수 값을 뒤로 이동 `moveEvenItemsToBack`

### 문제
연결 리스트에서 짝수 값을 가진 노드를 모두 뒤로 이동한다.
- `[1, 2, 3, 4, 5]` → `[1, 3, 5, 2, 4]`

### 풀이
Q3과 동일한 구조로 조건만 `% 2 == 0`으로 변경

---

## Q5. 연결 리스트 앞뒤 분할 `frontBackSplitLinkedList`

### 문제
연결 리스트를 앞 절반과 뒤 절반으로 분할한다.
- 홀수 개면 front가 하나 더 가짐
- `[1, 2, 3, 4, 5]` → front: `[1, 2, 3]`, back: `[4, 5]`

### 풀이
```c
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
    ListNode *cur = ll->head;
    int half = (ll->size + 1) / 2;  // 홀수면 front가 하나 더

    if (ll->head == NULL) return;

    resultFrontList->head = ll->head;
    resultFrontList->size = half;

    // front의 마지막 노드까지 이동
    for (int i = 0; i < half - 1; i++) {
        cur = cur->next;
    }

    resultBackList->head = cur->next;    // back의 시작 노드
    resultBackList->size = ll->size - half;

    cur->next = NULL;  // 두 리스트 분리
}
```

### 핵심 포인트
- `(size + 1) / 2` 로 front 크기 계산 (홀수 대응)
- `cur->next = NULL` 로 두 리스트를 끊어야 함

---

## Q6. 최댓값을 앞으로 이동 `moveMaxToFront`

### 문제
연결 리스트에서 최댓값을 찾아 맨 앞으로 이동한다.

### 이중 포인터를 쓰는 이유
함수 안에서 `head` 자체를 바꿔야 하기 때문이다.
- `ListNode *` 로 받으면 복사본이 전달되어 원본 head 변경 불가
- `ListNode **` 로 받으면 `*ptrHead = ...` 로 원본 head 변경 가능

### 풀이
```c
int moveMaxToFront(ListNode **ptrHead)
{
    if (*ptrHead == NULL) return 0;

    ListNode *cur = *ptrHead;   // 순회용 포인터
    ListNode *maxpre = NULL;    // 최댓값 노드의 이전 노드
    ListNode *max = *ptrHead;   // 최댓값 노드 (head로 초기화)
    ListNode *pre = NULL;       // cur의 이전 노드

    // 최댓값 탐색
    while (cur != NULL) {
        if (cur->item > max->item) {
            max = cur;
            maxpre = pre;
        }
        pre = cur;
        cur = cur->next;
    }

    // 최댓값이 이미 head이면 이동 불필요
    if (maxpre == NULL) return 1;

    maxpre->next = max->next;  // 최댓값 노드를 리스트에서 분리
    max->next = *ptrHead;      // 최댓값 노드가 기존 head를 가리키게
    *ptrHead = max;            // head를 최댓값 노드로 변경

    return 1;
}
```

### 핵심 포인트
- `maxpre` (최댓값의 이전 노드) 를 기억해야 분리 가능
- 연결 끊기 → 앞에 붙이기 → head 변경 순서 중요

---

## Q7. 재귀로 연결 리스트 역순 `RecursiveReverse`

### 문제
재귀를 이용하여 연결 리스트를 역순으로 뒤집는다.

### 재귀 동작 원리
```
[1] -> [2] -> [3] -> NULL

1. 끝까지 내려감: RecursiveReverse([3]) → return
2. [2]로 돌아와서: [3] -> [2], [2] -> NULL
3. [1]로 돌아와서: [2] -> [1], [1] -> NULL
결과: [3] -> [2] -> [1] -> NULL
```

### 풀이
```c
void RecursiveReverse(ListNode **ptrHead)
{
    ListNode *cur = *ptrHead;

    // 기저 조건: 빈 리스트이거나 마지막 노드
    if (cur == NULL || cur->next == NULL) return;

    ListNode *rest = cur->next;

    RecursiveReverse(&rest);     // 다음 노드부터 재귀로 뒤집기

    cur->next->next = cur;       // 다음 노드가 현재 노드를 가리키게
    cur->next = NULL;            // 현재 노드의 next 끊기

    *ptrHead = rest;             // head를 새 첫 번째 노드로 변경
}
```

### 핵심 포인트
- **끝까지 내려갔다가 돌아오면서** 하나씩 뒤집음
- `cur->next->next = cur` → 연결 방향 역전
- `cur->next = NULL` → 기존 연결 끊기
- `*ptrHead = rest` → head 업데이트
