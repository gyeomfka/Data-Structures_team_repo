//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
/**
alternateMergeLL() 함수를 작성하시오.
이 함수는 두 번째 연결 리스트(ll2)의 노드들을 첫 번째 연결 리스트(ll1) 의 교차 위치(alternate positions) 에 삽입하는 역할을 한다.
단, 첫 번째 리스트에 삽입할 교차 위치가 존재할 때만 두 번째 리스트의 노드를 삽입해야 한다.

void alternateMergeLL(LinkedList *ll1, LinkedList *ll2);

LinkedList1: 1 → 2 → 3
LinkedList2: 4 → 5 → 6 → 7

함수를 호출하면, 두 번째 리스트의 노드들이 첫 번째 리스트의 교차 위치에 삽입되어 다음과 같은 결과가 된다:

결과 LinkedList1: 1 → 4 → 2 → 5 → 3 → 6
결과 LinkedList2: 7

1. ll1 사이즈가 ll2 사이즈 보다 클 경우
2. ll2 사이즈가 ll1 사이즈 보다 클 경우
 */

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
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
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    ListNode *cur1 = ll1->head;
	ListNode *cur2 = ll2->head;

	ListNode *prev1 = NULL;
	ListNode *prev2 = NULL;

	if (cur1 == NULL || cur2 == NULL) {
		return;
	}

	while (cur1 != NULL && cur2 != NULL) {
		prev1 = cur1;
		cur1 = cur1->next;

		prev2 = cur2;
		cur2 = cur2->next;

		ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
		if (newNode == NULL) {
			return;
		}

		newNode->item = prev2->item;
		newNode->next = cur1;
		prev1->next = newNode;
		ll1->size++;
	}

	ListNode *temp = ll2->head;
	while (temp != cur2) {
		ListNode *next = temp->next;
		free(temp);
		temp = next;
	}

	ll2->head = cur2;
	/*
	if (cur2 != NULL) {
		cur2 = ll2->head;7
		for (int i = 0; i < ll1->size; i++) {
			prev2 = cur2;
			cur2 = cur2->next;
			free(prev2);
			ll2->head = cur2;
		}
	} else {
		removeAllItems(ll2);
	}
	*/

	/*
	남은 ll2의 요소들을 ll1으로 모두 복사하는 로직
	문제에서는 필요 없음
	if (cur2 != NULL) {
		cur2 = prev2;
		while (cur2 != NULL) {
			ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
			if (newNode == NULL) {
				return;
			}
			newNode->item = cur2->item;
			newNode->next = NULL;

			prev1->next = newNode;
			prev1 = newNode;

			cur2 = cur2->next;
			ll1->size++;
		}
	}
	removeAllItems(ll2);
	*/
}
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
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

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
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

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
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
