#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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

int peek(Stack* sp) {
    if (isEmpty(sp)) exit(1);
    else return sp->top->data;
}

void sortStack(Stack* sp) {
    Stack* tmpsp = createStack();
    while (!isEmpty(sp)) {
        int temp = sp->top->data;
        pop(sp);
        while (!isEmpty(tmpsp) && tmpsp->top->data > temp) {
            push(sp, tmpsp->top->data);
            pop(tmpsp);
        }
        push(tmpsp, temp);
    }
    while(!isEmpty(tmpsp)) push(sp, pop(tmpsp));
    free(tmpsp);
}

void printStack(Stack* sp) {
    if (isEmpty(sp)) {
        printf("Stack is empty\n");
    } else {
        Stack* tmpsp = createStack();
        printf("Stack elements: ");
        while(!isEmpty(sp)) {
            printf("%d ", peek(sp));
            push(tmpsp, pop(sp));
        }
        printf("\n");
        while(!isEmpty(tmpsp)) push(sp, pop(tmpsp));
        free(tmpsp);
    }
}

int main() {
    // Contoh penggunaan
    Stack* sp = createStack();
    push(sp, 44);
    push(sp, 63);
    push(sp, 5);
    push(sp, 26);
    push(sp, 14);
    printStack(sp);
    sortStack(sp);
    printStack(sp);
}