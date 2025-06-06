#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    unsigned size;
    Node *head;
    Node *tail;
} LinkedList;

Node* makeNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

bool isEmpty(LinkedList *ll) {
    return ll->head == NULL;
}

int getSize(LinkedList *ll) {
    return ll->size;
}

void initList(LinkedList *ll) {
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;
}

void pushBack(LinkedList *ll, int data) {
    Node *newNode = makeNode(data);
    if (newNode != NULL) {
        ll->size++;
        if (isEmpty(ll)) {
            newNode->next = newNode;
            ll->head = ll->tail = newNode;
        } else {
            newNode->next = ll->head;
            ll->tail->next = newNode;
            ll->tail = newNode;
        }
    }
}

void pushAt(LinkedList *ll, int data, int index) {
    if (index < 0) {
        printf("Index out of range\n");
        return;
    } else if (isEmpty(ll) || index == 0 || index > (int) ll->size) {
        pushBack(ll, data);
        if (index == 0) {
            ll->head = ll->tail;
            Node *temp = ll->head;
            while (temp->next != ll->head) temp = temp->next;
            ll->tail = temp;
        }
        return;    
    }
    
    Node *newNode = (makeNode(data));
    if (newNode != NULL) {
        Node *temp = ll->head;
        for (int i = 0;i < index-1; i++) temp = temp->next;
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
        ll->size++;
    }
}

void pushWhenFound(LinkedList *ll, int data, int compare) {
    if (isEmpty(ll)) {
        pushBack(ll, data);
        return;    
    }
    Node *newNode = (makeNode(data));
    if (newNode != NULL) {
        Node *temp = ll->head;
        int i;
        for (i = 0; (temp->data != compare) && (i <= (int) ll->size); i++) temp = temp->next;
        if (i >= (int) ll->size) {
            printf("Not found\n");
            return;
        } else {
            newNode->data = data;
            newNode->next = temp->next;
            temp->next = newNode;
            ll->size++;
        }
    }
}

void popBack(LinkedList *ll) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    } else {
        Node *temp = ll->head;
        if (ll->head == ll->tail) {
            ll->head = NULL;
            ll->tail = NULL;
            free(temp);
        } else {
            while (temp->next != ll->tail) temp = temp->next;
            ll->tail = temp;
            temp = temp->next;
            ll->tail->next = ll->head;
            free(temp);
        }
        ll->size--;
    }
}

void popFront(LinkedList *ll) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    } else {
        Node *temp = ll->head;
        if (ll->head == ll->tail) {
            ll->head = NULL;
            ll->tail = NULL;
            free(temp);
        } else {
            ll->head = temp->next;
            ll->tail->next = ll->head;
            free(temp);
        }
        ll->size--;
    }
}

void popAt(LinkedList *ll, int index) {
    if (index < 0 || index > (int) ll->size) {
        printf("Index out of range\n");
        return;
    } else if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    } else if (index == (int) ll->size-1) {
        popBack(ll);
        return;
    } else if (index == 0) {
        popFront(ll);
        return;
    } else {
        Node *temp = ll->head;
        for (int i = 0; i < index-1; i++) temp = temp->next;
        Node *toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        ll->size--;
    }
}

void popWhenFound(LinkedList *ll, int compare) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    }
    Node *temp = ll->head;
    Node *prev = ll->tail;
    int i;
    for (i = 0; (temp->data != compare) && (i <= (int) ll->size); i++) {
        prev = temp;
        temp = temp->next;
    }
    if (i >= (int) ll->size) {
        printf("Not found\n");
        return;
    } else if (temp == ll->head) {
        popFront(ll);
        return;
    } else if (temp == ll->tail) {
        popBack(ll);
        return;
    } else {
        prev->next = temp->next;
        free(temp);
        ll->size--;
    }
}

void popAll(LinkedList *ll) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    }
    Node *temp = ll->head;
    while (temp != ll->tail) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(temp);
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
}

int getBack(LinkedList *ll) {
    if (!isEmpty(ll)) return ll->tail->data;
    else {
        printf("Empty list\n");
        return 0;
    }
}

int getFront(LinkedList *ll) {
    if (!isEmpty(ll)) return ll->head->data;
    else {
        printf("Empty list\n");
        return 0;
    }
}

int getAt(LinkedList *ll, int index) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return 0;
    } else if (index >= (int) ll->size || index < 0) {
        printf("Index out of range\n");
        return 0;
    } else {
        Node *temp = ll->head;
        for (int i = 0; i < index; i++) temp = temp->next;
        return temp->data;
    }
}

void printList(LinkedList *ll) {
    if (isEmpty(ll)) {
        printf("Empty list\n");
        return;
    }
    Node *temp = ll->head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != ll->head);
    printf("\n");
}

// Untuk memenuhi perintah kedua yaitu membuat fungsi yang hanya ber-head (fungsi dibawah mendapat tail hanya dari head)
void getTail(LinkedList *ll) {
    if (!isEmpty(ll)) {
        Node *temp = ll->head;
        while (temp->next != ll->head) temp = temp->next;
        ll->tail = temp;
    }
}

int main() {
    // Contoh penggunaan
    LinkedList ll;
    initList(&ll);
    pushBack(&ll, 1);
    pushBack(&ll, 2);
    pushBack(&ll, 3);
    pushBack(&ll, 4);
    pushBack(&ll, 5);
    printList(&ll);
    printf("Size: %d\n", getSize(&ll));
    printf("Front: %d\n", getFront(&ll));
    printf("Back: %d\n", getBack(&ll));
    printf("At index 2: %d\n", getAt(&ll, 2));
    popFront(&ll);
    printList(&ll);
    popBack(&ll);
    printList(&ll);
    popAt(&ll, 1);
    printList(&ll);
    popWhenFound(&ll, 3);
    printList(&ll);
    popAll(&ll);
    printList(&ll);   
    return 0;
}