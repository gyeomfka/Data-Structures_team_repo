//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

/**
*insertSortedLL() 함수를 작성하시오.
이 함수는 사용자로부터 정수를 입력받은 뒤,
해당 값을 오름차순(ascending order) 으로 연결 리스트에 삽입해야 한다.

단,

현재 연결 리스트에 이미 동일한 값이 존재한다면 삽입을 허용하지 않는다.

함수는 새로운 항목이 삽입된 인덱스 위치(index position) 를 반환해야 한다.

삽입에 실패한 경우(예: 중복 값이거나 메모리 문제 등)에는 -1을 반환해야 한다.

또한,
현재 연결 리스트는 이미 정렬되어 있거나 비어 있는(empty) 상태라고 가정할 수 있다.
 */
//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);

void removeAllItems(LinkedList *ll);

ListNode *findNode(LinkedList *ll, int index);

int insertNode(LinkedList *ll, int index, int value);

int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: %d\n", j);
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
	if (newNode == NULL) return -1;

	newNode->item = item;
	newNode->next = NULL;

	if (ll->head == NULL) { // 제일 처음 insert 시
		ll->head = newNode;
		ll->size++;
		return 0;
	}

	ListNode *current = ll->head;
	int index = 0;

	if (current->item == newNode->item) {
		printf("중복불가1\n");
		free(newNode);
		return -1;
	}

	if (current->item > newNode->item) { // head값이 새로 입력하는 값보다 클 때 head값을 newNode로 교체한다.
		ll->head = newNode;
		newNode->next = current;
		ll->size++;
		return index;
	} else { // head 값이 새로 입려하는 값보다 작을때 순회한다.
		ListNode *previous = NULL;

		while (current->next != NULL) {
			if (current->item == newNode->item) {
				free(newNode);
				return -1;
			}

			previous = current;
			current = current->next;
			index++;

			if (current->item > newNode->item) {
				previous->next = newNode;
				newNode->next = current;
				ll->size++;
				return index;
			}
		}

		if (current->item == newNode->item) {
			free(newNode);
			return -1;
		}
		ll->size++;
		current->next = newNode;
		index++;
		return index;
	}
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
		printf("%d, ", cur->item);
		cur = cur->next;
	}
	printf("\n");
	printf("now size %d", ll->size);
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
