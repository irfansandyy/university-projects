#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int jobNumber;
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

Node* createNode(int jobNumber, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->jobNumber = jobNumber;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

PriorityQueue* createQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

bool isEmpty(PriorityQueue* pq) {
    return pq->head == NULL;
}

void enqueue(PriorityQueue* pq, int jobNumber, int priority) {
    Node* newNode = createNode(jobNumber, priority);

    if (isEmpty(pq) || pq->head->priority < priority) {
        newNode->next = pq->head;
        pq->head = newNode;
        return;
    }

    Node* temp = pq->head;
    while (temp->next != NULL && temp->next->priority >= priority) temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

void dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty! Nothing to delete.\n");
        return;
    }

    Node* temp = pq->head;
    pq->head = pq->head->next;
    printf("Deleted job with job number: %d and priority: %d\n", temp->jobNumber, temp->priority);
    free(temp);
}

void removeJob(PriorityQueue* pq, int jobNumber) {
    if (isEmpty(pq)) {
        printf("Queue is empty! Job not found.\n");
        return;
    }

    if (pq->head->jobNumber == jobNumber) {
        dequeue(pq);
        return;
    }

    Node* temp = pq->head;
    while (temp->next != NULL && temp->next->jobNumber != jobNumber) temp = temp->next;

    if (temp->next == NULL) {
        printf("Job with job number %d not found in the queue.\n", jobNumber);
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    printf("Removed job with job number: %d and priority: %d\n", toDelete->jobNumber, toDelete->priority);
    free(toDelete);
}

void displayQueue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty!\n");
        return;
    }

    Node* temp = pq->head;
    printf("Priority Queue:\n");
    while (temp != NULL) {
        printf("Job Number: %d, Priority: %d\n", temp->jobNumber, temp->priority);
        temp = temp->next;
    }
}

// Contoh penggunaan
int main() {
    PriorityQueue* pq = createQueue();

    enqueue(pq, 1, 3);
    enqueue(pq, 2, 5);
    enqueue(pq, 3, 2);
    enqueue(pq, 4, 4);

    displayQueue(pq);

    dequeue(pq);

    displayQueue(pq);

    removeJob(pq, 3);

    displayQueue(pq);

    removeJob(pq, 10);
    free(pq);

    return 0;
}