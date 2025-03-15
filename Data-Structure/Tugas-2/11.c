#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} LinkedList;

Node* makeNode(char data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtTail(LinkedList *ll, char data) {
    Node *newNode = makeNode(data);
    if (ll->head == NULL) {
        ll->head = newNode;
        ll->tail = newNode;
    } else {
        ll->tail->next = newNode;
        ll->tail = newNode;
    }
}

void deleteAll(LinkedList *ll) {
    Node *curr = ll->head;
    Node *next;
    if (curr == NULL) return;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void compareAndDelete(LinkedList *ll1, LinkedList *ll2) {
    Node *cPtr = NULL;
    Node *prev = NULL;
    bool found = true;

    while(ll1->head != NULL && ll2->head != NULL && found) {
        cPtr = ll2->head;
        found = false;
        while(cPtr != NULL) {
            if (ll1->head->data == cPtr->data) {
                found = true;
                if (ll1->head == ll1->tail) {
                    free(ll1->head);
                    ll1->head = NULL;
                    ll1->tail = NULL;
                } else {
                    Node *temp = ll1->head;
                    ll1->head = temp->next;
                    free(temp);
                }
                if(ll2->head == ll2->tail) {
                    free(ll2->head);
                    ll2->head = NULL;
                    ll2->tail = NULL;
                    break;
                }
                if (cPtr == ll2->tail) {
                    ll2->tail = prev;
                    prev->next = NULL;
                    free(cPtr);
                    break;
                } else if (cPtr == ll2->head) {
                    ll2->head = cPtr->next;
                    free(cPtr);
                    break;
                } else {
                    prev->next = cPtr->next;
                    free(cPtr);
                    break;
                }
            } else {
                prev = cPtr;
                cPtr = cPtr->next;
            }
        }
    }
    if (ll1->head != NULL || ll2->head != NULL) {
        printf("The words are not anagrams\n");
        deleteAll(ll1);
        deleteAll(ll2);
    } else {
        printf("The words are anagrams\n");
    }
    return;
}

void readAndInsertFromInput(LinkedList *ll1, LinkedList *ll2) {
    char c;
    printf("Enter two words to compare: ");
    
    bool isFirstWord = true;
    while (true) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        } else if (c == ' ' && isFirstWord) {
            isFirstWord = false;
            continue;
        } else if (c == ' ' && !isFirstWord) {
            break;
        }
        if (isFirstWord) insertAtTail(ll1, tolower(c));
        else insertAtTail(ll2, tolower(c));
    }
}

int main() {
    LinkedList ll1, ll2;
    ll1.head = NULL;
    ll1.tail = NULL;
    ll2.head = NULL;
    ll2.tail = NULL;
    readAndInsertFromInput(&ll1, &ll2);
    compareAndDelete(&ll1, &ll2);
    return 0;
}