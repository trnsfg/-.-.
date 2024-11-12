#include <iostream>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->data) insert(node->left, value);
        else if (value > node->data) insert(node->right, value);
    }

    Node* find(Node* node, const T& value) {
        if (!node) return nullptr;
        if (value == node->data) return node;
        if (value < node->data) return find(node->left, value);
        return find(node->right, value);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void copy(Node*& dest, Node* src) {
        if (!src) {
            dest = nullptr;
            return;
        }
        dest = new Node(src->data);
        copy(dest->left, src->left);
        copy(dest->right, src->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree<T>& other) : root(nullptr) {
        copy(root, other.root);
    }

    BinaryTree(BinaryTree<T>&& other) : root(other.root) {
        other.root = nullptr;
    }

    BinaryTree<T>& operator=(const BinaryTree<T>& other) {
        if (this == &other) return *this;
        clear(root);
        copy(root, other.root);
        return *this;
    }

    void insert(const T& value) {
        insert(root, value);
    }

    bool search(const T& value) {
        return find(root, value) != nullptr;
    }

    void print(Node* node) const {
        if (!node) return;
        print(node->left);
        std::cout << node->data << " ";
        print(node->right);
    }

    void print() const {
        print(root);
        std::cout << std::endl;
    }

    ~BinaryTree() {
        clear(root);
    }
};

int main() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    std::cout << "Binary tree: ";
    tree.print();

    std::cout << "Search for 10: " << (tree.search(10) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 25: " << (tree.search(25) ? "Found" : "Not Found") << std::endl;

    return 0;
}
