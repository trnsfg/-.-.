#include <iostream>
#include <string>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList<T>& other) : head(nullptr) {
        Node* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
    }

    LinkedList(LinkedList<T>&& other) : head(other.head) {
        other.head = nullptr;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this == &other) return *this;
        clear();
        Node* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
        return *this;
    }

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    std::cout << "Linked list: ";
    list.print();

    LinkedList<int> copyList = list;
    std::cout << "Copied linked list: ";
    copyList.print();

    LinkedList<int> movedList = std::move(list);
    std::cout << "Moved linked list: ";
    movedList.print();

    return 0;
}
