#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

Node* createNode(int data) {
    Node* np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->next = NULL;
    return np;
}

Queue* createQueue() {
    Queue* qp = (Queue*) malloc(sizeof(Queue));
    qp->head = NULL;
    qp->tail = NULL;
    return qp;
}

bool isEmpty(Queue* qp) {
    return (qp->head == NULL && qp->tail == NULL);
}

void push(Queue* qp, int data) {
    Node* np = createNode(data);
    if (isEmpty(qp))                 
        qp->head = qp->tail = np;
    else {
        qp->tail->next = np;
        qp->tail = np;
    }
}

void pop(Queue* qp) {
    if (!isEmpty(qp)) {
        Node* temp = qp->head;
        qp->head = qp->head->next;
        free(temp);
        if (qp->head == NULL) qp->tail = NULL;
    }
}

int front(Queue* qp) {
    if (!isEmpty(qp)) {
        return (qp->head->data);
    }
    return (int)0;
}

int main() {
    Queue* qp = createQueue();
    int N, S;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        int data;
        scanf("%d", &data);
        push(qp, data);
    }
    scanf("%d", &S);
    for(int i = 0; i < S; i++) {
        char text[10];
        scanf("%s", text);
        if(strcmp(text, "BERHASIL")==0) {
            pop(qp);
        } else if(strcmp(text, "GAGAL")==0) {
            push(qp, front(qp));
            pop(qp);
        }
    }
    if(isEmpty(qp)) {
        printf("KOSONG");
        return 0;
    }
    while(!isEmpty(qp)) {
        printf("%d ", front(qp));
        pop(qp);
    }
    return 0;
}