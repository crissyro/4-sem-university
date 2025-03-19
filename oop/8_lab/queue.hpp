#include <stdexcept>
#include <vector>


template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* frontPtr;
    Node* rearPtr;
    size_t count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }

        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        Node* temp = frontPtr;
        T data = temp->data;

        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }

        delete temp;
        count--;

        return data;
    }

    inline bool isEmpty() const {
        return frontPtr == nullptr;
    }

    inline size_t size() const {
        return count;
    }

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() const {
            return current->data;
        }
    };

    Iterator begin() {
        return Iterator(frontPtr);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};