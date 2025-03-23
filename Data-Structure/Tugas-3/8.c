#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAX_EQUATION 200

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
    return (sp->top == NULL);
}

void push(Stack* sp, char data) {
    Node* np = createNode(data);
    np->next = sp->top;
    sp->top = np;
}

char pop(Stack* sp) {
    if (isEmpty(sp)) exit(1);
    else {
        Node* np = sp->top;
        char tempData = np->data;
        sp->top = np->next;
        free(np);
        return tempData;
    }
}

char peek(Stack* sp) {
    if (isEmpty(sp)) exit(1);
    else return sp->top->data;
}

int precedence(char c) {
    switch (c) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

int infixToPostfix(char infix[], char post[]) {
    char token, c, temp;
    int size = 0;
    Stack* sp = createStack();
    
    for (long long unsigned i = 0; i < strlen(infix); i++) {
        token = infix[i];
        if (token == ' ') {
            continue;
        } else if (isdigit(token)) {
            post[size++] = token;
        } else if (token == '(') {
            temp = token;
            push(sp, temp);
        } else if (token == ')') {
            while ((c = pop(sp)) != '(') post[size++] = c;
        } else {
            while (!isEmpty(sp) && precedence(peek(sp)) >= precedence(token)) post[size++] = pop(sp);
            temp = token;
            push(sp, temp);
        }
    }

    while (!isEmpty(sp)) post[size++] = pop(sp);
    post[size] = '\0';
    free(sp);
    return size;
}

void printList(char post[], int n) {
    for (int i = 0; i < n; i++) printf("%c ", post[i]);
}

int main() {
    char postfix[MAX_EQUATION], infix[MAX_EQUATION];
    // printf("Type an infix expression:\n");
    // fgets(infix, MAX_EQUATION, stdin);
    strcpy(infix, "(2 + 3) * (8 / 4) - 6");
    int n = infixToPostfix(infix, postfix);
    printf("\nThe postfix form is:\n");
    printList(postfix, n);
    printf("\n");
}