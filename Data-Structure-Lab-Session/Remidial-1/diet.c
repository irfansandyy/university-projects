#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define llu long long unsigned

typedef struct pqueueNode_t {
    llu data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, llu value)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value > pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while (temp->next != NULL && temp->next->data > value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

llu pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->_size = 0;
    pq->_top = NULL;
    return pq;
}

int main() {
    PriorityQueue* pq = createPriorityQueue();
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        llu data;
        scanf("%llu", &data);
        pqueue_push(pq, data);
    }
    while(!pqueue_isEmpty(pq)) {
        if(pq->_top->next == NULL) break;
        llu R = pqueue_top(pq);
        pqueue_pop(pq);
        llu T = pqueue_top(pq);
        pqueue_pop(pq);
        if(R == T) {
            continue;
        } else if(R > T) {
            pqueue_push(pq, R - T);
        } else if(R < T) {
            pqueue_push(pq, T - R);
        }
    }
    if(pqueue_isEmpty(pq)) {
        printf("0");
    } else {
        printf("%llu", pqueue_top(pq));
    }
}