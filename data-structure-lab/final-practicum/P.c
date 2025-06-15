#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int data;
    int priority;
} Request;

typedef struct node {
    Request data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} PriorityQueue;

bool isEmpty(PriorityQueue *pq) {
    return (pq->top == NULL);
}

void push(PriorityQueue *pq, Request data) {
    Node *temp = pq->top;
    Node *np = (Node*) malloc (sizeof(Node));
    np->data = data;
    np->next = NULL;

    if (isEmpty(pq)) {
        pq->top = np;
        return;
    }

    if (data.data <= pq->top->data.data && data.priority < pq->top->data.priority) {
        np->next = pq->top;
        pq->top = np;
    }
    else {
        while (temp->next != NULL && (temp->next->data.data > data.data && temp->next->data.priority <= data.priority)) temp = temp->next;
        np->next = temp->next;
        temp->next = np;
    }
}

void pop(PriorityQueue *pq) {
    if (!isEmpty(pq)) {
        Node *temp = pq->top;
        pq->top = pq->top->next;
        free(temp);
    }
}

Request *top(PriorityQueue *pq) {
    if (!isEmpty(pq)) return &pq->top->data;
    else return NULL;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->top = NULL;
    return pq;
}

int main() {
    int p, q;
    PriorityQueue *pq = createPriorityQueue();
    PriorityQueue *temp = createPriorityQueue();
    int time = 0;
    int countdown[26] = {0};
    int count[26] = {0};

    scanf("%d", &p);
    scanf("%d", &q);

    char content;
    Request req;
    for(int i = 0; i < p; i++) {
        scanf("%c", &content);
        int data = (int) content - 'A';
        req.data = data;
        req.priority = count[data]++;
        push(pq, req);
    }

    while(!isEmpty(pq)) {
        if(countdown[top(pq)->data] == 0) {
            for(int i = 0; i < 26; i++) {
                
            }
            countdown[top(pq)->data] += q;
        } 
    }
}