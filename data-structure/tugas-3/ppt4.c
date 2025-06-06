#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_STACK 100

// Stack dengan static array
typedef struct {
    int top;
    int data[MAX_STACK];
} Stack;

Stack* createStack() {
    Stack* sp = (Stack*) malloc(sizeof(Stack));
    sp ->top = -1;
    return sp;
}

bool isFull(Stack* sp) {
    return sp->top == MAX_STACK - 1;
}

bool isEmpty(Stack* sp) {
    return sp->top < 0;
}

void push(Stack* sp, int data) {
    if (isFull(sp)) {
        printf("Stack is full\n");
    } else {
        sp->data[++sp->top] = data;
    }
}

int pop(Stack* sp) {
    if (isEmpty(sp)) {
        printf("Stack is empty\n");
        return INT_MIN;
    } else {
        int temp = sp->data[sp->top];
        sp->top--;
        return temp;
    }
}

int peek(Stack* sp) {
    if (isEmpty(sp)) {
        printf("Stack is empty\n");
        return INT_MIN;
    } else {
        return sp->data[sp->top];
    }
}

void findByValue(Stack* sp, int data) {
    int* tempArr = (int*)malloc((sp->top + 1) * sizeof(int));
    int i = sp->top;
    int max = sp->top;
    int foundIndex[sp->top + 1];
    int found = 0;

    for (; i >= 0; i--) {
        tempArr[i] = pop(sp);
        if (tempArr[i] == data) {
            foundIndex[found] = i;
            found++;
        }
    }

    for (int j = i + 1; j <= max; j++) push(sp, tempArr[j]);
    free(tempArr);
    if (!found) printf("Element %d not found\n", data);
    for (int j = 0; j < found; j++) {
        printf("Element %d found at %d index from top and %d index from bottom\n", data, max - foundIndex[j], foundIndex[j]);
    }
}

void findByIndex(Stack* sp, int index) {
    if (index < 0 || index > sp->top) {
        printf("Index out of range\n");
    } else {
        int* tempArr = (int*)malloc((sp->top + 1) * sizeof(int));
        int i = sp->top;
        int max = sp->top;

        for (; i > index; i--) tempArr[i] = pop(sp);
        printf("Element at index %d from bottom is %d\n", index, peek(sp));
        for (int j = i + 1; j <= max; j++) push(sp, tempArr[j]);
        free(tempArr);
    }
}

void editByIndex(Stack* sp, int index, int data) {
    if (index < 0 || index > sp->top) {
        printf("Index out of range\n");
    } else {
        int* tempArr = (int*)malloc((sp->top + 1) * sizeof(int));
        int i = sp->top;
        int max = sp->top;

        for (; i >= index; i--) tempArr[i] = pop(sp);
        push(sp, data);
        printf("Element at index %d from bottom is changed to %d\n", index, data);
        for (int j = i + 2; j <= max; j++) {
            push(sp, tempArr[j]);
        }
        free(tempArr);
    }
}

void editByValue(Stack* sp, int oldData, int newData) {
    int* tempArr = (int*)malloc((sp->top + 1) * sizeof(int));
    int i = sp->top;
    int max = sp->top;
    int foundIndex[sp->top + 1];
    int found = 0;

    for (; i >= 0; i--) {
        tempArr[i] = pop(sp);
        if (tempArr[i] == oldData) {
            foundIndex[found] = i;
            found++;
        }
    }
    
    for (int j = i + 1; j <= max; j++) {
        for (int k = 0; k < found; k++) {
            if (j == foundIndex[k]) {
                printf("Element %d at %d index from top and %d index from bottom changed to %d\n", oldData, max - foundIndex[k], foundIndex[k], newData);
                push(sp, newData);
            } else push(sp, tempArr[j]);
        }
    }
    
    if (!found) printf("Element %d not found\n", oldData);
    free(tempArr);
}

void printStack(Stack* sp) {
    if (isEmpty(sp)) {
        printf("Stack is empty\n");
    } else {
        int* tempArr = (int*)malloc((sp->top + 1) * sizeof(int));
        int max = sp->top;
        printf("Stack elements: ");
        for (int i = sp->top; i >= 0; i--) {
            tempArr[i] = pop(sp);
            printf("%d ", tempArr[i]);
        }
        printf("\n");
        for (int i = 0; i <= max; i++) push(sp, tempArr[i]);
        free(tempArr);
    }
}

int main() {
    // Contoh penggunaan
    Stack* sp = createStack();
    push(sp, 1);
    push(sp, 2);
    push(sp, 3);
    push(sp, 4);
    push(sp, 5);
    printStack(sp);
    findByValue(sp, 3);
    findByIndex(sp, 2);
    editByIndex(sp, 2, 10);
    printStack(sp);
    editByValue(sp, 10, 20);
    printStack(sp);
    pop(sp);
    printStack(sp);
    free(sp);
    return 0;
}