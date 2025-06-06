#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    int numOfDigits;
    Node *head;
    Node *tail;
} LinkedList;

Node* makeNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(LinkedList *ll, int data) {
    Node *newNode = makeNode(data);
    ll->numOfDigits++;
    if (ll->head == NULL) {
        ll->head = newNode;
        ll->tail = newNode;
    } else {
        newNode->next = ll->head;
        ll->head = newNode;
    }
}

void readAndInsertFromInput(LinkedList *n1, LinkedList *n2) {
    char c;
    for(int i = 1; i <= 2; i++) {
        printf("Enter integer %d: ", i);
        while(true) {
            c = getchar();
            if (c == '\n' || c == EOF) {
                break;
            } else if (c == ' ' || c == ',' || c == '.') {
                continue;
            } else if (!isdigit(c)) {
                printf("Please input numbers\n");
                exit(1);
            } else {
                if (i == 1) insertAtHead(n1, (int)(c - '0'));
                else if (i == 2) insertAtHead(n2, (int)(c - '0'));
                else exit(1);
            }
        }
    }
}

void reversePrint(LinkedList *ll) {
    if (ll->head == NULL) {
        printf("Empty list\n");
        return;
    }
    int *arr = (int*)malloc(ll->numOfDigits * sizeof(int));
    
    Node *curr = ll->head;
    for(int i = 0; i < ll->numOfDigits && curr != NULL; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
    
    for(int i = ll->numOfDigits - 1; i >= 0; i--) {
        printf("%d", arr[i]);
    }
    printf("\n");
    free(arr);
}

LinkedList addDigits(LinkedList *n1, LinkedList *n2) {
    LinkedList r;
    Node *curr1, *curr2;
    int carry = 0, sum = 0;

    r.head = NULL;
    r.tail = NULL;
    r.numOfDigits = 0;

    curr1 = n1->head;
    curr2 = n2->head;
    
    int maxDigits = (n1->numOfDigits > n2->numOfDigits ? n1->numOfDigits : n2->numOfDigits) + 1;
    int *sumDigits = (int*)malloc(maxDigits * sizeof(int));
    int digitCount = 0;
    
    while(curr1 != NULL || curr2 != NULL || carry != 0) {
        sum = carry;
        if (curr1 != NULL) {
            sum += curr1->data;
            curr1 = curr1->next;
        }
        if (curr2 != NULL) {
            sum += curr2->data;
            curr2 = curr2->next;
        }
        sumDigits[digitCount++] = sum % 10;
        carry = sum / 10;
    }
    
    for (int i = digitCount - 1; i >= 0; i--) {
        insertAtHead(&r, sumDigits[i]);
    }
    
    free(sumDigits);
    return r;
}

int main() {
    LinkedList n1, n2, r;
    n1.head = NULL;
    n1.tail = NULL;
    n1.numOfDigits = 0;
    n2.head = NULL;
    n2.tail = NULL;
    n2.numOfDigits = 0;

    readAndInsertFromInput(&n1, &n2);
    printf("Number 1: ");
    reversePrint(&n1);
    printf("Number 2: ");
    reversePrint(&n2);
    printf("Sum: ");
    r = addDigits(&n1, &n2);
    reversePrint(&r);
    return 0;
}