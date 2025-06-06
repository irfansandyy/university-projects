#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} LinkedList;

Node* createNode(int data) {
    Node* np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->next = NULL;
    return np;
}

LinkedList* createList() {
    LinkedList* llp = (LinkedList*) malloc(sizeof(LinkedList));
    llp->head = NULL;
    llp->tail = NULL;
    return llp;
}

bool isEmpty(LinkedList* llp) {
    return llp->head == NULL;
}

void pushHead(LinkedList* llp, int data) {
    Node* np = createNode(data);
    if(isEmpty(llp)) {
        llp->head = np;
        llp->tail = np;
    } else {
        np->next = llp->head;
        llp->head = np;
    }
}

void pushTail(LinkedList* llp, int data) {
    Node* np = createNode(data);
    if(isEmpty(llp)) {
        llp->head = np;
        llp->tail = np;
    } else {
        llp->tail->next = np;
        llp->tail = np;
    }
}

int popHead(LinkedList* llp) {
    if(isEmpty(llp)) {
        return 0;
    } else {
        int tempInt = llp->head->data;
        Node* tempNode = llp->head;
        llp->head = llp->head->next;
        free(tempNode);
        return tempInt;
    }
}

int popTail(LinkedList* llp) {
    if(isEmpty(llp)) {
        return 0;
    } else {
        int tempInt = llp->tail->data;
        Node* tempNode = llp->head;
        while(tempNode->next != llp->tail) {
            tempNode = tempNode->next;
        }
        free(llp->tail);
        llp->tail = tempNode;
        llp->tail->next = NULL;
        return tempInt;
    }
}

void swapData(LinkedList* llp) {
    Node* ptr1 = llp->head;
    Node* ptr2 = llp->head->next;
    Node* ptr2next;
    Node* ptr1Ahead;
    Node* ptr2Ahead;
    if(llp->head->next != NULL) {    
        llp->head = llp->head->next;
    }
    while(ptr1 != NULL && ptr2 != NULL) {
        if(ptr2->next != NULL) {
            ptr1Ahead = ptr1->next->next;
            ptr2Ahead = ptr2->next->next;
        } else {
            ptr1Ahead = NULL;
            ptr2Ahead = NULL;
        }
        if(ptr2->next == NULL) {
            ptr2next = NULL;
        } else if(ptr2->next->next == NULL) {
            ptr2next = ptr2->next;
        } else {
            ptr2next = ptr2->next->next;
        }
        ptr2->next = ptr1;
        ptr1->next = ptr2next;
        ptr1 = ptr1Ahead;
        ptr2 = ptr2Ahead;
    }
}

int main() {
    LinkedList* llp = createList();
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        int data;
        scanf("%d", &data);
        pushTail(llp, data);
    }
    swapData(llp);
    while(llp->head != NULL) {
        printf("%d ", popHead(llp));
    }

    return 0;
}