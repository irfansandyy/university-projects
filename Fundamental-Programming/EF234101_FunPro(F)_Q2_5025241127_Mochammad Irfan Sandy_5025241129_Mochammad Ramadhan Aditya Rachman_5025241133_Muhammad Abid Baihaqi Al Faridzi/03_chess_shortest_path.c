#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 8

typedef struct {
    int x, y;
    int distance;
} Cell;

int rowMoves[] = {2, 2, -2, -2, 1, 1, -1, -1};
int colMoves[] = {-1, 1, -1, 1, 2, -2, 2, -2};

int isValid(int x, int y) {
    return (x >= 0 && y >= 0 && x < N && y < N);
}

typedef struct QueueNode {
    Cell cell;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head, *tail;
} Queue;

void initQueue(Queue *queue) {
    queue->head = queue->tail = NULL;
}

void enqueue(Queue *queue, int x, int y, int distance) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->cell.x = x;
    newNode->cell.y = y;
    newNode->cell.distance = distance;
    newNode->next = NULL;
    if(queue->tail) {
        queue->tail->next = newNode;
    } else {
        queue->head = newNode;
    }
    queue->tail = newNode;
}

Cell dequeue(Queue *queue) {
    if(queue->head == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }
    QueueNode *temp = queue->head;
    Cell cell = temp->cell;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    free(temp);
    return cell;
}

int isEmpty(Queue *queue) {
    return queue->head == NULL;
}

int findMinSteps(int startX, int startY, int destX, int destY) {
    if (startX == destX && startY == destY) return 0;

    int visited[N][N] = {0};
    Queue queue;
    initQueue(&queue);

    enqueue(&queue, startX, startY, 0);
    visited[startX][startY] = 1;

    while (!isEmpty(&queue)) {
        Cell cell = dequeue(&queue);

        for (int i = 0; i < 8; i++) {
            int newX = cell.x + rowMoves[i];
            int newY = cell.y + colMoves[i];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                if (newX == destX && newY == destY) {
                    return cell.distance + 1;
                }
                enqueue(&queue, newX, newY, cell.distance + 1);
                visited[newX][newY] = 1;
            }
        }
    }
    return INT_MAX;
}

int main() {
    int startX, startY, destX, destY;

    printf("Enter starting position (row col): ");
    scanf("%d %d", &startX, &startY);
    printf("Enter destination position (row col): ");
    scanf("%d %d", &destX, &destY);

    int steps = findMinSteps(startX, startY, destX, destY);
    printf("Steps required: %d\n", steps);

    return 0;
}