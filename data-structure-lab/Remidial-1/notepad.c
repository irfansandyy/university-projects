#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct {
    Node* top;
} Stack;

Node* createNode(char data) {
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
    return sp->top == NULL;
}

void push(Stack* sp, char data) {
    Node* np = createNode(data);
    if(isEmpty(sp)) {
        sp->top = np;
    } else {
        np->next = sp->top;
        sp->top = np;
    }
}

char pop(Stack* sp) {
    if(isEmpty(sp)) {
        return 0;
    } else {
        char tempChar = sp->top->data;
        Node* tempNode = sp->top;
        sp->top = sp->top->next;
        free(tempNode);
        return tempChar;
    }
}

void printStack(Stack* sp) {
    Stack* tmpsp = createStack();
    while(!isEmpty(sp)) push(tmpsp, pop(sp));
    while(!isEmpty(tmpsp)) {
        char data = pop(tmpsp);
        printf("%c", data);
        push(sp, data);
    }
    free(tmpsp);
}

int main() {
    Stack* sp = createStack();
    char choice[10];
    while(true) {
        scanf("%s", choice);
        if(strcmp(choice, "WRITE")==0) {
            char data;
            scanf("%c", &data);
            scanf("%c", &data);
            push(sp, data);
        } else if(strcmp(choice, "BACKSPACE")==0) {
            pop(sp);
            continue;
        } else if(strcmp(choice, "PRINT")==0){
            printStack(sp);
            break;
        }
    }
}