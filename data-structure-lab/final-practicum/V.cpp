#include <iostream>
#include <string>

struct BST {
    public:
        BST() {
            this->root = nullptr;
            this->size = 0;
        }

        bool isEmpty() const {
            return !this->root;
        }

        int find(int value) const {
            return searchUtil(this->root, value);
        }

        void insert(int value) {
            if (find(value) == -1) {
                this->root = insertUtil(this->root, value);
                size++;
            }
        }

        void remove(int value) {
            if (find(value) != -1) {
                this->root = removeUtil(this->root, value);
                size--;
            }
        }

        void traverseInOrder() const {
            if(!isEmpty()) {
                inOrder(this->root);
                std::cout << "\n";
            } else {
                std::cout << "EMPTY\n";
            }
        }

    private:
        struct Node {
            int key;
            Node *left, *right;
            Node(int k) {
                this->key = k;
                this->left = this->right = nullptr;
            }
        };

        Node *root;
        unsigned int size;

        int searchUtil(Node *node, int value) const {
            int depth = 1;
            while (node) {
                if (value < node->key) {
                    node = node->left;
                    depth++;
                } else if (value > node->key) {
                    node = node->right;
                    depth++;
                } else return depth;
            }
            return -1;
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
                std::cout << node->key << " ";
                inOrder(node->right);
            }
        }
};

int main() {
    BST tree;
    int N;
    std::cin >> N;

    std::string cmd;
    int x;
    for(int i = 0; i < N; i++) {
        std::cin >> cmd;
        if(cmd == "INSERT") {
            std::cin >> x;
            tree.insert(x);
        } else if(cmd == "SEARCH") {
            std::cin >> x;
            std::cout << tree.find(x);
            std::cout << "\n";
        } else if(cmd == "DELETE") {
            std::cin >> x;  
            tree.remove(x);
        } else if(cmd == "PRINT") {
            tree.traverseInOrder();
        }
    }

    return 0;
}