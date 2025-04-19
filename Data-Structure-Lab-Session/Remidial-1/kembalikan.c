#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} LinkedList;

Node* createNode(int data) {
    Node* np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->next = NULL;
    np->prev = NULL;
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

void pushTail(LinkedList* llp, int data) {
    Node* np = createNode(data);
    if(isEmpty(llp)) {
        llp->head = np;
        llp->tail = np;
    } else {
        llp->tail->next = np;
        np->prev = llp->tail;
        llp->tail = np;
    }
}

int popTail(LinkedList* llp) {
    if(isEmpty(llp)) {
        return 0;
    } else {
        Node *temp;
        int tempData = llp->tail->data;
        if (llp->head == llp->tail) {
            temp = llp->head;
            llp->head = NULL;
            llp->tail = NULL;
            free(temp);
        }
        else {
            temp = llp->tail;
            llp->tail = llp->tail->prev;
            llp->tail->next = NULL;
            free(temp);
        }
        return tempData;
    }
}

int main() {
    LinkedList* lp = createList();
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        int data;
        scanf("%d", &data);
        pushTail(lp, data);
    }
    LinkedList* rlp = createList();
    while(!isEmpty(lp)) {
        pushTail(rlp, popTail(lp));
    }
    free(lp);
    Node* ptr = rlp->head;
    while(ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}