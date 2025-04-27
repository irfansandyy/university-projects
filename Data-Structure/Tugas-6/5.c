#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

Node* minNode(Node* node) {
    while (node && node->left != NULL) node = node->left;
    return node;
}

Node* maxNode(Node* node) {
    while (node && node->right != NULL) node = node->right;
    return node;
}

Node* createSuccessor(Node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) {
        Node* temp = root->right;
        free(root);
        return temp;
    } else if (root->right == NULL) {
        Node* temp = root->left;
        free(root);
        return temp;
    } else {
        Node* successor = minNode(root->right);
        root->data = successor->data;
        Node* parent = root;
        Node* curr = root->right;
        while (curr != NULL && curr->data != successor->data) {
            parent = curr;
            if (successor->data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (parent->left == curr) parent->left = createSuccessor(curr);
        else parent->right = createSuccessor(curr);
        return root;
    }
}

Node* createPredecessor(Node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) {
        Node* temp = root->right;
        free(root);
        return temp;
    } else if (root->right == NULL) {
        Node* temp = root->left;
        free(root);
        return temp;
    } else {
        Node* predecessor = maxNode(root->left);
        root->data = predecessor->data;
        Node* parent = root;
        Node* curr = root->left;
        while (curr != NULL && curr->data != predecessor->data) {
            parent = curr;
            if (predecessor->data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (parent->right == curr) parent->right = createPredecessor(curr);
        else parent->left = createPredecessor(curr);
        return root;
    }
}

int main() {
    return 0;
}