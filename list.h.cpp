#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>
#include <stdexcept>

//шаблонний абстрактний клас для списку
template <typename T>
class List {
public:
    virtual ~List() = default;

    virtual void add(const T& element) = 0;
    virtual T get(size_t index) const = 0;
    virtual void remove(size_t index) = 0;
    virtual size_t size() const = 0;
    virtual bool isEmpty() const = 0;

    void print() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << get(i) << "\n";
        }
    }
};

template <typename T>
class ArrayList : public List<T> {
private:
    std::vector<T> data;

public:
    void add(const T& element) override {
        data.push_back(element);
    }

    T get(size_t index) const override {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void remove(size_t index) override {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
    }

    size_t size() const override {
        return data.size();
    }

    bool isEmpty() const override {
        return data.empty();
    }
};

//реалізація на основі двобічно зв'язного списку
template <typename T>
class LinkedList : public List<T> {
private:
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node(T val) : value(val) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t count = 0;

public:
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void add(const T& element) override {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    T get(size_t index) const override {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    void remove(size_t index) override {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }

        Node* toDelete;
        if (index == 0) {
            toDelete = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (index == count - 1) {
            toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete toDelete;
        count--;
    }

    size_t size() const override {
        return count;
    }

    bool isEmpty() const override {
        return count == 0;
    }
};

#endif // LIST_H