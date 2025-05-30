#include <iostream>

struct BST {
    private:
        struct Node {
            int key;
            unsigned int count;
            Node *left, *right;
            Node(int k) {
                this->key = k;
                this->count = 1u;
                this->left = this->right = nullptr;
            }
        };

        Node *root;
        unsigned int size;

        Node* searchUtil(Node *node, int value) const {
            while (node) {
                if (value < node->key) node = node->left;
                else if (value > node->key) node = node->right;
                else return node;
            }
            return nullptr;
        }

        Node* insertUtil(Node *node, int value) {
            if (!node) return new Node(value);

            if (value < node->key) node->left = insertUtil(node->left, value);
            else if (value > node->key) node->right = insertUtil(node->right, value);

            return node;
        }

        Node* findMinNode(Node *node) const {
            Node *currNode = node;
            while (currNode && currNode->left) currNode = currNode->left;

            return currNode;
        }

        Node* removeUtil(Node *node, int value) {
            if (!node) return nullptr;

            if (value > node->key) node->right = removeUtil(node->right, value);
            else if (value < node->key) node->left = removeUtil(node->left, value);
            else {
                if (!node->left) {
                    Node *rightChild = node->right;
                    delete node;
                    return rightChild;
                }
                else if (!node->right) {
                    Node *leftChild = node->left;
                    delete node;
                    return leftChild;
                }

                Node *temp = findMinNode(node->right);
                node->key = temp->key;
                node->right = removeUtil(node->right, temp->key);
            }
            return node;
        }

        void inOrder(Node *node) const {
            if (node) {
                inOrder(node->left);
                std::cout << node->key << "(" << node->count << ") ";
                inOrder(node->right);
            }
        }

        void postOrder(Node *node) const {
            if (node) {
                postOrder(node->left);
                postOrder(node->right);
                std::cout << node->key << "(" << node->count << ") ";
            }
        }

        void preOrder(Node *node) const {
            if (node) {
                std::cout << node->key << "(" << node->count << ") ";
                preOrder(node->left);
                preOrder(node->right);
            }
        }
    public:
        BST() {
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
            } else {
                Node *node = searchUtil(this->root, value);
                node->count++;
            }
        }

        void remove(int value) {
            if (find(value)) {
                Node *node = searchUtil(this->root, value);
                if(node->count == 1) {
                    this->root = removeUtil(this->root, value);
                    size--;
                } else {
                    node->count--;
                }
            }
        }

        void traverseInOrder() const {
            inOrder(this->root);
        }

        void traversePreOrder() const {
            preOrder(this->root);
        }

        void traversePostOrder() const {
            postOrder(this->root);
        }
};

int main() {
    BST tree;
    int N, x;
    std::string input;
    std::cin >> N;
    for(int i = 0; i < N; i++) {
        std::cin >> input;
        if(input.compare("insert") == 0) {
            std::cin >> x;
            tree.insert(x);
        } else if(input.compare("remove") == 0) {
            std::cin >> x;
            tree.remove(x);
        } else if(input.compare("inorder") == 0) {
            tree.traverseInOrder();
            std::cout << "\n";
        } else if(input.compare("preorder") == 0) {
            tree.traversePreOrder();
            std::cout << "\n";
        } else if(input.compare("postorder") == 0) {
            tree.traversePostOrder();
            std::cout << "\n";
        }
    }
}