#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct tNode {
	int data;
	struct tNode *next;
} tNode;

typedef tNode *Node;

int flag = FALSE;
void insert(Node *start, int data);
void bubbleSort(Node start);
void swap(Node a, Node b);
void print(Node start);

int main() {
	int initArr[] = {10, 50, 15, 1, 100};
	Node start = NULL;
	for(int i = 0; i < (int)(sizeof(initArr)/sizeof(int)); i++) insert(&start, initArr[i]);
	print(start);
	printf(" -> before sorting");
	printf("\nInput: ");
	int input;
	scanf("%d", &input);	
	insert(&start, input);
	bubbleSort(start);
	print(start);
	printf(" -> after sorting");
	return 0;
}

void insert(Node *start, int data) {
	Node temp = (Node)malloc(sizeof(tNode));
	temp->data = data;
	temp->next = *start;
	*start = temp;	
}

void print(Node start) {
	Node temp = start;
	while(temp->next != NULL) {
		printf("%d, ", temp->data);
		temp = temp->next;
	}
	printf("%d", temp->data);
	return;
}

void bubbleSort(Node start) {
	int listSize = 0;
	Node temp;
	Node temp1;
	if(start == NULL) return;

	temp = start;
	do {
		listSize++;
		temp = temp->next;
	} while(temp != NULL);

	for(; listSize > 0; listSize--) {
		temp = start;
		temp1 = temp->next;
		while(temp1 != NULL) {
			if(temp->data > temp1->data) {
				swap(temp, temp1);
			}
			temp = temp->next;
			temp1 = temp1->next;
		}
		temp = start;
		temp1 = temp->next;
	}
	flag = TRUE;
}

void swap(Node a, Node b) {
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}