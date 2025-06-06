#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

Node* preorderSearch(Node* root, int target) {
    if (root == NULL) return NULL;

    if (root->data == target) return root;

    Node* left = preorderSearch(root->left, target);
    if (left != NULL) return left;

    return preorderSearch(root->right, target);
}

Node* inorderSearch(Node* root, int target) {
    if (root == NULL) return NULL;

    Node* left = inorderSearch(root->left, target);
    if (left != NULL) return left;

    if (root->data == target) return root;

    return inorderSearch(root->right, target);
}

Node* postorderSearch(Node* root, int target) {
    if (root == NULL) return NULL;

    Node* left = postorderSearch(root->left, target);
    if (left != NULL) return left;

    Node* right = postorderSearch(root->right, target);
    if (right != NULL) return right;

    if (root->data == target) return root;

    return NULL;
}

int main() {
    return 0;
}