#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *makeNode(int data, Node *next) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = next;
    return newNode;
}

void insertNode(int n, Node **head, Node **tail) {
    *head = makeNode(1, NULL);
    (*head)->next = *head;
    *tail = *head;
    
    for(int i = 2; i <= n; i++) {
        Node *newNode = makeNode(i, *head);
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void checkAndDelete(int m, Node **head, Node **tail) {
    Node *curr = *head;
    Node *prev = *tail;
    
    while(*head != *tail) {
        for(int i = 1; i < m; i++) {
            prev = curr;
            curr = curr->next;
        }
        
        printf("Removing child %d\n", curr->data);
        prev->next = curr->next;
        if(curr == *head) *head = curr->next;
        else if(curr == *tail) *tail = prev;
        
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    int n = 0, m = 1;
    char c;

    printf("Input the number of children (n): ");
    scanf("%d", &n);
    getchar();
    printf("Input words (m): ");
    
    while(true) {
        c = getchar();
        if (c == '\n' || c == EOF) break;
        else if (c == ' ') m++;
    }

    insertNode(n, &head, &tail);
    checkAndDelete(m, &head, &tail);
    
    if (head != NULL) {
        printf("The last child standing is: %d\n", head->data);
        free(head);
    }
    
    return 0;
}