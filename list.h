#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

//шаблонний абстрактний клас (інтерфейс) для списку
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
    T* data;
    size_t currentSize;
    size_t capacity;

    //приватний метод для розширення масиву
    void resize() {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    ArrayList() : data(nullptr), currentSize(0), capacity(0) {
        resize(); // Початкове виділення пам'яті
    }

    ~ArrayList() {
        delete[] data;
    }

    void add(const T& element) override {
        //якщо місця більше немає, розширюємо масив
        if (currentSize >= capacity) {
            resize();
        }
        //додаємо новий елемент і збільшуємо лічильник
        data[currentSize] = element;
        currentSize++;
    }

    T get(size_t index) const override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void remove(size_t index) override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        //зсуваємо всі елементи праворуч від видаленого на одну позицію вліво
        for (size_t i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    size_t size() const override {
        return currentSize;
    }

    bool isEmpty() const override {
        return currentSize == 0;
    }
};

template <typename T>
class LinkedList : public List<T> {
private:
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;
        explicit Node(T val) : value(val) {}
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

        Node* toDelete = head;
        if (index == 0) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else {
            for (size_t i = 0; i < index; ++i) {
                toDelete = toDelete->next;
            }
            toDelete->prev->next = toDelete->next;
            if (toDelete->next) toDelete->next->prev = toDelete->prev;
            else tail = toDelete->prev;
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