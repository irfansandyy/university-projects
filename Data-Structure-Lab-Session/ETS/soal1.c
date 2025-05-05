#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_CHAR 200

typedef struct {
    int x;
    int y;
} Robot;

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Node *createNode(char data) {
    Node *np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->next = NULL;
    return np;
}

Stack *createStack() {
    Stack *sp = (Stack*) malloc(sizeof(Stack));
    sp->top = NULL;
    return sp;
}

bool isEmpty(Stack *sp) {
    return sp->top == NULL;
}

void push(Stack *sp, char data) {
    Node *np = createNode(data);
    np->next = sp->top;
    sp->top = np;
}

char pop(Stack* sp) {
    if(isEmpty(sp)) exit(1);
    else {
        char tempChar = sp->top->data;
        Node* tempNode = sp->top;
        sp->top = sp->top->next;
        free(tempNode);
        return tempChar;
    }
}

int main() {
    Robot robot;
    Stack *sp = createStack();
    char input[MAX_CHAR];
    robot.x = 0;
    robot.y = 0;

    printf("Masukkan perintah gerakan robot: \n");
    scanf("%s", input);
    for(long unsigned int i = 0; i < strlen(input); i++) {
        if(input[i] == 'B') pop(sp);
        else push(sp, input[i]);
    }

    while(!isEmpty(sp)) {
        char move = pop(sp);
        if(move == 'U') robot.y++;
        else if(move == 'D') robot.y--;
        else if(move == 'R') robot.x++;
        else if(move == 'L') robot.x--;
        else exit(1);
    }

    printf("Posisi Akhir Robot: (%d,%d)\n", robot.x, robot.y);

    return 0;
}