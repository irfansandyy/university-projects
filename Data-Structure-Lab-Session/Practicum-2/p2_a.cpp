#include <iostream>
#include <vector>

struct AVL {
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

        Node* findMinNode(Node *node) const {
            Node *currNode = node;
            while (currNode && currNode->left) currNode = currNode->left;
            return currNode;
        }

        Node* removeUtil(Node* node, int value) {
            if(!node) return node;
            if(value > node->data) node->right = removeUtil(node->right, value);
            else if(value < node->data) node->left = removeUtil(node->left, value);
            else {
                Node *temp;
                if(!node->left || !node->right) {
                    temp = nullptr;
                    if(!node->left) temp=node->right;  
                    else if(!node->right) temp=node->left;

                    if(!temp){
                        temp = node;
                        node = nullptr;
                    }
                    else *node = *temp;   

                    delete temp;
                } else {
                    temp = findMinNode(node->right);
                    node->data = temp->data;
                    node->right = removeUtil(node->right, temp->data);
                }    
            }

            if(!node) return node;
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            int balanceFactor = getBalanceFactor(node);

            if(balanceFactor > 1 && getBalanceFactor(node->left) >= 0) 
                return leftCaseRotate(node);
            if(balanceFactor > 1 && getBalanceFactor(node->left) < 0) 
                return leftRightCaseRotate(node);
            if(balanceFactor < -1 && getBalanceFactor(node->right) <= 0) 
                return rightCaseRotate(node);
            if(balanceFactor < -1 && getBalanceFactor(node->right) > 0) 
                return rightLeftCaseRotate(node);

            return node;
        }

        std::vector<int> findWithPathUtil(Node* node, int value) const {
            std::vector<int> path;
            std::vector<int> zeroVector;
            while (node) {
                path.push_back(node->data);
                if (value < node->data) node = node->left;
                else if (value > node->data) node = node->right;
                else return path;
            }
            return zeroVector;
        }

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

        std::vector<int> findWithPath(int value) const {
            return findWithPathUtil(this->root, value);
        }

        void insert(int value) {
            if (!find(value)) {
                this->root = insertUtil(this->root, value);
                size++;
                std::cout << value << " inserted\n";
            } else {
                std::cout << value << " is already in the tree\n";
            }
        }

        void remove(int value) {
            if (find(value)) {
                this->root = removeUtil(this->root, value);
                size--;
                std::cout << value << " deleted\n";
            } else {
                std::cout << value << " is not found in the tree\n";
            }
        }
};

int main() {
    AVL tree;
    int N, x;
    std::string input;
    std::cin >> N;
    for(int i = 0; i < N; i++) {
        std::cin >> input >> x;
        if(input.compare("INSERT") == 0) {
            tree.insert(x);
        } else if(input.compare("DELETE") == 0) {
            tree.remove(x);
        } else if(input.compare("FIND") == 0) {
            std::vector<int> path = tree.findWithPath(x);
            if(path.empty()) {
                std::cout << x << " not found\n";
            } else {
                std::cout << x << " found with path: ";
                for(auto p : path) std::cout << p << " ";
                std::cout << "\n";
            }
        }
    }
}