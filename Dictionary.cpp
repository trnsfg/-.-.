#include <iostream>
#include <string>

class Dictionary {
private:
    struct Node {
        std::string english;
        std::string ukrainian;
        int count;
        Node* left;
        Node* right;
        Node(const std::string& eng, const std::string& ukr)
            : english(eng), ukrainian(ukr), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void insert(Node*& node, const std::string& eng, const std::string& ukr) {
        if (!node) {
            node = new Node(eng, ukr);
            return;
        }
        if (eng < node->english) insert(node->left, eng, ukr);
        else if (eng > node->english) insert(node->right, eng, ukr);
        else {
            node->count++;
            node->ukrainian = ukr;
        }
    }

    Node* find(Node* node, const std::string& eng) {
        if (!node) return nullptr;
        if (eng == node->english) return node;
        if (eng < node->english) return find(node->left, eng);
        return find(node->right, eng);
    }

    void deleteNode(Node*& node, const std::string& eng) {
        if (!node) return;
        if (eng < node->english) deleteNode(node->left, eng);
        else if (eng > node->english) deleteNode(node->right, eng);
        else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if (!node->left) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (!node->right) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* minNode = findMin(node->right);
                node->english = minNode->english;
                node->ukrainian = minNode->ukrainian;
                node->count = minNode->count;
                deleteNode(node->right, minNode->english);
            }
        }
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void collectWords(Node* node, Node* words[], int& index) {
        if (!node) return;
        collectWords(node->left, words, index);
        words[index++] = node;
        collectWords(node->right, words, index);
    }

    void printTop3(Node* words[], int count) {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (words[i]->count < words[j]->count) {
                    Node* temp = words[i];
                    words[i] = words[j];
                    words[j] = temp;
                }
            }
        }

        std::cout << "Top 3 popular words:" << std::endl;
        for (int i = 0; i < 3 && i < count; ++i) {
            std::cout << words[i]->english << " - " << words[i]->ukrainian
                << " (count: " << words[i]->count << ")" << std::endl;
        }
    }

    void printBottom3(Node* words[], int count) {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (words[i]->count > words[j]->count) {
                    Node* temp = words[i];
                    words[i] = words[j];
                    words[j] = temp;
                }
            }
        }

        std::cout << "Top 3 unpopular words:" << std::endl;
        for (int i = 0; i < 3 && i < count; ++i) {
            std::cout << words[i]->english << " - " << words[i]->ukrainian
                << " (count: " << words[i]->count << ")" << std::endl;
        }
    }

public:
    Dictionary() : root(nullptr) {}

    void insert(const std::string& eng, const std::string& ukr) {
        insert(root, eng, ukr);
    }

    void search(const std::string& eng) {
        Node* result = find(root, eng);
        if (result) {
            std::cout << result->english << " - " << result->ukrainian << " (count: " << result->count << ")" << std::endl;
        }
        else {
            std::cout << "Word not found!" << std::endl;
        }
    }

    void print(Node* node) const {
        if (!node) return;
        print(node->left);
        std::cout << node->english << " - " << node->ukrainian << " (count: " << node->count << ")" << std::endl;
        print(node->right);
    }

    void print() const {
        print(root);
    }

    void remove(const std::string& eng) {
        deleteNode(root, eng);
    }

    void top3Popular() {
        Node* words[100];
        int index = 0;
        collectWords(root, words, index);
        printTop3(words, index);
    }

    void top3Unpopular() {
        Node* words[100];
        int index = 0;
        collectWords(root, words, index);
        printBottom3(words, index);
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    Dictionary dict;
    dict.insert("hello", "привiт");
    dict.insert("world", "свiт");
    dict.insert("bye", "пока");
    dict.insert("hello", "привiт");

    dict.search("hello");
    dict.print();
    dict.remove("world");
    dict.print();

    dict.top3Popular();
    dict.top3Unpopular();

    return 0;
}
