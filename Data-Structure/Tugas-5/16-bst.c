#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100

int bst[MAX_SIZE];
int pos = 1; 

typedef struct node {
    int data;
    struct node *left, *right;
} Node;

typedef struct {
    Node* root;
} BinaryTree;

Node* createNode(int data) {
    Node* np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->left = NULL;
    np->right = NULL;
    return np;
}

BinaryTree* createTree() {
    BinaryTree* tp = (BinaryTree*) malloc(sizeof(BinaryTree));
    tp->root = NULL;
    return tp;
}

bool isEmpty(BinaryTree* tp) {
    return tp->root == NULL;
}

void insert(BinaryTree* tp, Node* curr, int data) {
    if (isEmpty(tp)) {
        tp->root = createNode(data);
        return;
    }

    if (data < curr->data) {
        if (curr->left != NULL)
            insert(tp, curr->left, data);
        else
            curr->left = createNode(data);
    } else if (data > curr->data) {
        if (curr->right != NULL)
            insert(tp, curr->right, data);
        else
            curr->right = createNode(data);
    }
}

void preOrder(Node* np) {
    if (np != NULL) {
        printf("%d ", np->data);
        preOrder(np->left);
        preOrder(np->right);
    }
}

void inOrder(Node* np) {
    if (np != NULL) {
        inOrder(np->left);
        printf("%d ", np->data);
        inOrder(np->right);
    }
}

void postOrder(Node* np) {
    if (np != NULL) {
        postOrder(np->left);
        postOrder(np->right);
        printf("%d ", np->data);
    }
}


void bubbleSort(int arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

void sortToBST(int sorted[], int left, int right) {
    if (left > right) return;
    int mid = (left + right) / 2;
    bst[pos++] = sorted[mid];
    sortToBST(sorted, left, mid - 1);
    sortToBST(sorted, mid + 1, right);
}

int main() {
    BinaryTree* tp = createTree();
    int num[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int n = sizeof(num) / sizeof(num[0]);
    bubbleSort(num, n);
    sortToBST(num, 0, n-1);
    printf("BST Input Array: \n");
    for(int i = 0; i < n; i++) printf("%d ", bst[i]);
    for(int i = 0; i < n; i++) insert(tp, tp->root, bst[i]);
    printf("Pre Order: \n");
    preOrder(tp->root);
    printf("In Order: \n");
    inOrder(tp->root);
    printf("Post Order: \n");
    postOrder(tp->root);
}