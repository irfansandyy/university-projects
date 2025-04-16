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

bool isVocal(char data) {
    return (data == 'a' || data == 'i' || data == 'u' || data == 'e' || data == 'o' || data == 'A' || data == 'I' || data == 'U' || data == 'E' || data == 'O');
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

int main() {
    Stack* sp = createStack();
    char text[101];
    scanf("%s", text);
    for(long unsigned int i = 0; i < strlen(text); i++) {
        if(isVocal(text[i])) {
            push(sp, text[i]);
            push(sp, text[i]);
        } else {
            push(sp, text[i]);
        }
    }
    while(sp->top != NULL) {
        printf("%c", pop(sp));
    }

    return 0;
}