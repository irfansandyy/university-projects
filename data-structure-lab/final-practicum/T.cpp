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
                this->root = insertUtil(this->root, value);
                size++;
            }
        }

    private:
        struct Node {
            int data;
            int height;
            Node *left, *right;
            Node(int d) {
                this->data = d;
                this->height = 1;
                this->left = this->right = nullptr;
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
            newParent->left = pivotNode;

            pivotNode->height = 
                max(getHeight(pivotNode->left), getHeight(pivotNode->right)) + 1;
            newParent->height = 
                max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

            return newParent;
        }

        Node* leftCaseRotate(Node* node) {
            std::cout << "Left Case\n";
            std::cout << "PivotNode: " << node->data << "\n";
            std::cout << "PivotNode->left: " << node->left->data << "\n";
            std::cout << "PivotNode->left->left: " << node->left->left->data << "\n\n";

            Node* newNode = rightRotate(node);
            std::cout << "result:\n";
            std::cout << "NewNode: " << newNode->data << "\n";
            std::cout << "NewNode->left: " << newNode->left->data << "\n";
            std::cout << "NewNode->right: " << newNode->right->data << "\n\n";
            return newNode;
        }

        Node* rightCaseRotate(Node* node) {
            std::cout << "Right Case\n";
            std::cout << "PivotNode: " << node->data << "\n";
            std::cout << "PivotNode->right: " << node->right->data << "\n";
            std::cout << "PivotNode->right->right: " << node->right->right->data << "\n\n";

            Node* newNode = leftRotate(node);
            std::cout << "result:\n";
            std::cout << "NewNode: " << newNode->data << "\n";
            std::cout << "NewNode->left: " << newNode->left->data << "\n";
            std::cout << "NewNode->right: " << newNode->right->data << "\n\n";
            return newNode;
        }

        Node* leftRightCaseRotate(Node* node) {
            std::cout << "Left Right Case\n";
            std::cout << "PivotNode: " << node->data << "\n";
            std::cout << "PivotNode->left: " << node->left->data << "\n";
            std::cout << "PivotNode->left->right: " << node->left->right->data << "\n\n";

            node->left = leftRotate(node->left);
            Node* newNode = rightRotate(node);

            std::cout << "result:\n";
            std::cout << "NewNode: " << newNode->data << "\n";
            std::cout << "NewNode->left: " << newNode->left->data << "\n";
            std::cout << "NewNode->right: " << newNode->right->data << "\n\n";
            return newNode;
        }

        Node* rightLeftCaseRotate(Node* node) {
            std::cout << "Right Left Case\n";
            std::cout << "PivotNode: " << node->data << "\n";
            std::cout << "PivotNode->right: " << node->right->data << "\n";
            std::cout << "PivotNode->right->left: " << node->right->left->data << "\n\n";

            node->right = rightRotate(node->right);
            Node* newNode = leftRotate(node);

            std::cout << "result:\n";
            std::cout << "NewNode: " << newNode->data << "\n";
            std::cout << "NewNode->left: " << newNode->left->data << "\n";
            std::cout << "NewNode->right: " << newNode->right->data << "\n\n";
            return newNode;
        }

        int getBalanceFactor(Node* node) const {
            if(!node) return 0;
            return getHeight(node->left) - getHeight(node->right);
        }

        Node* insertUtil(Node* node, int value) {
            if(!node) return new Node(value);
            if(value < node->data) node->left = insertUtil(node->left, value);
            else if(value > node->data) node->right = insertUtil(node->right, value);

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
};

int main() {
    AVL set;
    int N, a;
    std::cin >> N;

    for(int i = 0; i < N; i++) {
        std::cin >> a;
        set.insert(a);
    }

    return 0;
}