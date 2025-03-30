#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 5

// Circular Queue dengan Array
typedef struct {
    int data[MAX];
    int head;
    int tail;
} CircularQueue;

CircularQueue* createQueue() {
    CircularQueue* cq = (CircularQueue*) malloc(sizeof(CircularQueue));
    cq->head = -1;
    cq->tail = -1;
}

bool isFull(CircularQueue *cq) {
    return (cq->head == 0 && cq->tail == MAX - 1) || (cq->tail == (cq->head - 1) % (MAX - 1));
}

bool isEmpty(CircularQueue *cq) {
    return cq->head == -1;
}

int getQueueSize(CircularQueue *cq) {
    if (isEmpty(cq)) return 0;
    if (cq->tail >= cq->head) return cq->tail - cq->head + 1;
    else return (MAX - cq->head) + (cq->tail + 1);
}

void enqueue(CircularQueue *cq, int value) {
    if (isFull(cq)) {
        printf("Queue is full!\n");
        return;
    }

    if (cq->head == -1) cq->head = cq->tail = 0;
    else if (cq->tail == MAX - 1 && cq->head != 0) cq->tail = 0;
    else cq->tail++;

    cq->data[cq->tail] = value;
}

int dequeue(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }

    int data = cq->data[cq->head];
    cq->data[cq->head] = -1;

    if (cq->head == cq->tail) cq->head = cq->tail = -1;
    else if (cq->head == MAX - 1) cq->head = 0;
    else cq->head++;

    return data;
}

void findByValue(CircularQueue *cq, int value) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return;
    }

    CircularQueue* tempQueue = createQueue();
    int relativeIndex = 0;
    bool valueFound = false;

    printf("Value %d found at index: ", value);
    while (!isEmpty(cq)) {
        int temp = dequeue(cq);
        if (temp == value) {
            printf("%d ", relativeIndex);
            valueFound = true;
        }
        enqueue(tempQueue, temp);
        relativeIndex++;
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    if (!valueFound) printf("not found in the queue");
    printf("\n");
}

int findByIndex(CircularQueue *cq, int index) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return -1;
    } else if (index < 0 || index >= getQueueSize(cq)) {
        printf("Invalid index!\n");
        return -1;
    }

    CircularQueue* tempQueue = createQueue();
    int relativeIndex = 0;
    int valueAtIndex = -1;

    while (!isEmpty(cq)) {
        int temp = dequeue(cq);
        if (relativeIndex == index) valueAtIndex = temp;
        enqueue(tempQueue, temp);
        relativeIndex++;
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    if (valueAtIndex != -1) printf("Value at index %d: %d\n", index, valueAtIndex);
    else printf("Invalid index!\n");

    return valueAtIndex;
}

void editByIndex(CircularQueue *cq, int index, int new) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return;
    } else if (index < 0 || index >= getQueueSize(cq)) {
        printf("Invalid index!\n");
        return;
    }

    CircularQueue* tempQueue = createQueue();
    int relativeIndex = 0;

    while (!isEmpty(cq)) {
        int temp = dequeue(cq);
        if (relativeIndex == index) temp = new;
        enqueue(tempQueue, temp);
        relativeIndex++;
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    printf("Value at index %d updated to %d\n", index, new);
}

void editByValue(CircularQueue *cq, int oldValue, int newValue) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return;
    }

    CircularQueue* tempQueue = createQueue();
    bool valueUpdated = false;

    while (!isEmpty(cq)) {
        int temp = dequeue(cq);
        if (temp == oldValue) {
            temp = newValue;
            valueUpdated = true;
        }
        enqueue(tempQueue, temp);
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    if (valueUpdated) printf("Value %d updated to %d\n", oldValue, newValue);
    else printf("Value %d not found in the queue\n", oldValue);
}

int getTotal(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return 0;
    }

    CircularQueue* tempQueue = createQueue();
    int total = 0;

    while (!isEmpty(cq)) {
        int value = dequeue(cq);
        total += value;
        enqueue(tempQueue, value);
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    return total;
}

float getAverage(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return 0.0;
    }

    int total = getTotal(cq);
    int size = getQueueSize(cq);
    return (float)total / size;
}

int getMax(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }

    CircularQueue* tempQueue = createQueue();
    int max = INT_MIN;

    while (!isEmpty(cq)) {
        int value = dequeue(cq);
        if (value > max) max = value;
        enqueue(tempQueue, value);
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    return max;
}

int getMin(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }

    CircularQueue* tempQueue = createQueue();
    int min = INT_MAX;

    while (!isEmpty(cq)) {
        int value = dequeue(cq);
        if (value < min) min = value;
        enqueue(tempQueue, value);
    }

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
    return min;
}

void displayQueue(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return;
    }

    CircularQueue* tempQueue = createQueue();
    printf("Elements: ");
    while (!isEmpty(cq)) {
        int value = dequeue(cq);
        printf("%d ", value);
        enqueue(tempQueue, value);
    }
    printf("\n");

    while (!isEmpty(tempQueue)) enqueue(cq, dequeue(tempQueue));
    free(tempQueue);
}

// Contoh penggunaan
int main() {
    CircularQueue* cq = createQueue();

    enqueue(cq, 10);
    enqueue(cq, 20);
    enqueue(cq, 30);
    enqueue(cq, 40);
    enqueue(cq, 50);

    displayQueue(cq);

    dequeue(cq);
    dequeue(cq);

    displayQueue(cq);

    enqueue(cq, 60);
    enqueue(cq, 70);
    enqueue(cq, 80);

    displayQueue(cq);

    findByValue(cq, 30);
    findByValue(cq, 100);
    findByIndex(cq, 2);
    findByIndex(cq, 10);
    editByIndex(cq, 2, 99);

    displayQueue(cq);

    editByValue(cq, 40, 88);

    displayQueue(cq);

    editByValue(cq, 100, 77);

    displayQueue(cq);

    printf("Total: %d\n", getTotal(cq));
    printf("Average: %.2f\n", getAverage(cq));
    printf("Maximum: %d\n", getMax(cq));
    printf("Minimum: %d\n", getMin(cq));

    free(cq);

    return 0;
}