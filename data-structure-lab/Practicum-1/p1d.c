#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// kode priority queue dari modul strukdat
typedef struct pqueueNode_t {
    int data;
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value)
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

int pqueue_top(PriorityQueue *pqueue) {
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

int toInteger(char data[]) {
    int sum = 0;
    for(long unsigned int i = 0; i < strlen(data); i++) {
        int num = 0;
        if(data[i] == ')') num = 0;
        else if(data[i] == '!') num = 1;
        else if(data[i] == '@') num = 2;
        else if(data[i] == '#') num = 3;
        else if(data[i] == '$') num = 4;
        else if(data[i] == '%') num = 5;
        else if(data[i] == '^') num = 6;
        else if(data[i] == '&') num = 7;
        else if(data[i] == '*') num = 8;
        else if(data[i] == '(') num = 9;
        for(long unsigned int j = 0; j < (strlen(data) - 1 - i); j++) {
            num = num*10;
        }
        sum += num;
    }
    return sum;
}

int main() {
    PriorityQueue* pq = createPriorityQueue();
    int n, M;
    scanf("%d %d", &n, &M);
    for(int i = 0; i < n; i++) {
        char data[21];
        scanf("%s", data);
        int parsedData = toInteger(data);
        if (parsedData <= M) pqueue_push(pq, parsedData);
        while((pqueue_top(pq) >= M) && !pqueue_isEmpty(pq)) {
            printf("%d ", pqueue_top(pq));
            pqueue_pop(pq);
            M--;
        }
        printf("\n");
    }
    
    return 0;
}