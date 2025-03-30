#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Stack
typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node* top;
} Stack;

Node* createNode(int data) {
    Node* np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->next = NULL;
    return np;
}

Stack* createStack() {
    Stack* sp = (Stack*) malloc(sizeof(Stack));
    sp->top = NULL;
    return sp;
}

bool isEmpty(Stack* sp) {
    return (sp->top == NULL);
}

void push(Stack* sp, int data) {
    Node* np = createNode(data);
    np->next = sp->top;
    sp->top = np;
}

int pop(Stack* sp) {
    if (isEmpty(sp)) exit(1);
    else {
        Node* np = sp->top;
        int tempData = np->data;
        sp->top = np->next;
        free(np);
        return tempData;
    }
}

// Queue
typedef struct {
    Stack* stack1;
    Stack* stack2;
} Queue;

Queue* createQueue() {
    Queue* qp = (Queue*) malloc(sizeof(Queue));
    qp->stack1 = createStack();
    qp->stack2 = createStack();
    return qp;
}

void enqueue(Queue* qp, int data) {
    push(qp->stack1, data);
}

int dequeue(Queue* qp) {
    if (isEmpty(qp->stack2)) {
        while (!isEmpty(qp->stack1)) {
            push(qp->stack2, pop(qp->stack1));
        }
    }

    if (isEmpty(qp->stack2)) exit(1);
    return pop(qp->stack2);
}

void displayQueue(Queue* qp) {
    if (isEmpty(qp->stack1) && isEmpty(qp->stack2)) {
        printf("Queue is empty!\n");
        return;
    }

    Stack* tempStack = createStack();
    while (!isEmpty(qp->stack2)) push(tempStack, pop(qp->stack2));

    printf("Elements: ");
    Node* temp = qp->stack1->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    temp = tempStack->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    while (!isEmpty(tempStack)) push(qp->stack2, pop(tempStack));
    free(tempStack);
}

// Contoh penggunaan
int main() {
    Queue* qp = createQueue();

    enqueue(qp, 10);
    enqueue(qp, 20);
    enqueue(qp, 30);
    enqueue(qp, 40);

    displayQueue(qp);

    dequeue(qp);
    dequeue(qp);

    displayQueue(qp);

    enqueue(qp, 50);
    enqueue(qp, 60);

    displayQueue(qp);
    return 0;
}