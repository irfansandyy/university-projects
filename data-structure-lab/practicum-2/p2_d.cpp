#include <iostream>

struct AVL {
    public:
        AVL() {
            this->root = nullptr;
            this->size = 0;
        }

        bool isEmpty() const {
            return !this->root;
        }

        bool find(int value) const {
            return searchUtil(this->root, value);
        }

        void insert(int value) {
            if (!find(value)) {
                this->root = insertUtil(this->root, value, nullptr);
                size++;
            }
        }

        void traverseInOrder() const {
            inOrder(this->root);
        }
    
    private:
        struct Node {
            int data;
            int height;
            Node *left, *right, *parent;
            Node(int d, Node* p) {
                this->data = d;
                this->height = 1;
                this->left = this->right = nullptr;
                this->parent = p;
            }
        };

        Node *root;
        unsigned size;

        Node* searchUtil(Node *node, int value) const {
            while (node) {
                if (value < node->data) node = node->left;
                else if (value > node->data) node = node->right;
                else return node;
            }
            return nullptr;
        }

        int getHeight(Node* node) const {
            if(!node) return 0; 
            return node->height;
        }

        int max(int a, int b) const {
            return (a > b)? a : b;
        }

        Node* rightRotate(Node* pivotNode) {
            Node* newParent = pivotNode->left;
            pivotNode->left = newParent->right;
            pivotNode->parent = newParent;
            newParent->parent = nullptr;
            if(pivotNode->left) pivotNode->left->parent = pivotNode;
            newParent->right = pivotNode;

            pivotNode->height = 
                max(getHeight(pivotNode->left), getHeight(pivotNode->right)) + 1;
            newParent->height = 
                max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

            return newParent;
        }

        Node* leftRotate(Node* pivotNode) {
            Node* newParent = pivotNode->right;
            pivotNode->right = newParent->left;
            pivotNode->parent = newParent;
            newParent->parent = nullptr;
            if(pivotNode->right) pivotNode->right->parent = pivotNode;
            newParent->left = pivotNode;

            pivotNode->height = 
                max(getHeight(pivotNode->left), getHeight(pivotNode->right)) + 1;
            newParent->height = 
                max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

            return newParent;
        }

        Node* leftCaseRotate(Node* node) {
            return rightRotate(node);
        }

        Node* rightCaseRotate(Node* node) {
            return leftRotate(node);
        }

        Node* leftRightCaseRotate(Node* node) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        Node* rightLeftCaseRotate(Node* node) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        int getBalanceFactor(Node* node) const {
            if(!node) return 0;
            return getHeight(node->left) - getHeight(node->right);
        }

        Node* insertUtil(Node* node, int value, Node* lastNode) {
            if(!node) return new Node(value, lastNode);
            if(value < node->data) node->left = insertUtil(node->left, value, node);
            else if(value > node->data) node->right = insertUtil(node->right, value, node);

            node->height = max(getHeight(node->left), getHeight(node->right)) + 1; 
            int balanceFactor = getBalanceFactor(node);

            if(balanceFactor > 1 && value < node->left->data)
                return leftCaseRotate(node);
            if(balanceFactor > 1 && value > node->left->data)
                return leftRightCaseRotate(node);
            if(balanceFactor < -1 && value > node->right->data)
                return rightCaseRotate(node);
            if(balanceFactor < -1 && value < node->right->data)
                return rightLeftCaseRotate(node);

            return node;
        }

        void inOrder(Node *node) const {
            if (node) {
                inOrder(node->left);
                std::cout << (node->parent ? node->parent->data : -1) << " ";
                inOrder(node->right);
            }
        }
};

int main() {
    AVL tree;
    int N, a;
    std::cin >> N;
    for(int i = 0; i < N; i++) {
        std::cin >> a;
        tree.insert(a);
    }
    tree.traverseInOrder();
}