#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue);
bool queue_isEmpty(Queue *queue);
void queue_push(Queue *queue, int value);
void queue_pop(Queue *queue);
int  queue_front(Queue *queue);
int  queue_size(Queue *queue);

void queue_init(Queue *queue) {
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int value) {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

int queue_front(Queue *queue) {
    if (!queue_isEmpty(queue)) {
        return (queue->_front->data);
    }
    return (int)0;
}

int queue_size(Queue *queue) {
    return queue->_size;
}

int main() {
    Queue* qp = (Queue*)malloc(sizeof(Queue));
    queue_init(qp);

    int X, Y, Z;
    scanf("%d %d %d", &X, &Y, &Z);
    for(int i = 0; i < X; i++) {
        int data;
        scanf("%d", &data);
        queue_push(qp, data);
    }

    int queueBack = 0;
    for(int i = 1; Y > 0 && !queue_isEmpty(qp); i++) {
        if (i % Z == 0) {
            queue_push(qp, queue_front(qp));
            queue_pop(qp);
            queueBack++;
            continue;
        }
        if (Y - queue_front(qp) >= 0) {
            Y = Y - queue_front(qp);
        } else break;
        queue_pop(qp);
    }

    if(queue_isEmpty(qp)) printf("%d Yes Dapat burger gratis!!!", queueBack);
    else printf("%d NOO tidak Dapat :(", queueBack);

    return 0;
}