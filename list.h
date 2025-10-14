#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>
#include <utility>

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

    //метод для зміни елемента за індексом
    virtual void set(size_t index, const T& element) = 0;

    //метод для обміну двох елементів місцями
    virtual void swap(size_t index1, size_t index2) {
        if (index1 >= size() || index2 >= size()) {
            throw std::out_of_range("Index out of range for swap");
        }
        T temp = get(index1);
        set(index1, get(index2));
        set(index2, temp);
    }

    void print() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << get(i) << "\n";
        }
    }
};

//низькорівнева реалізація ArrayList
template <typename T>
class ArrayList : public List<T> {
private:
    T* data;
    size_t currentSize;
    size_t capacity;

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
        resize();
    }

    ~ArrayList() {
        delete[] data;
    }

    void add(const T& element) override {
        if (currentSize >= capacity) {
            resize();
        }
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

    void set(size_t index, const T& element) override {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range for set");
        }
        data[index] = element;
    }

    void swap(size_t index1, size_t index2) override {
        if (index1 >= currentSize || index2 >= currentSize) {
            throw std::out_of_range("Index out of range for swap");
        }
        std::swap(data[index1], data[index2]);
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

    Node* getNode(size_t index) const {
        if (index >= count) return nullptr;
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

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

        Node* toDelete = getNode(index); // Використовуємо getNode
        if (!toDelete) return; // Додаткова перевірка

        if (toDelete->prev) toDelete->prev->next = toDelete->next;
        else head = toDelete->next; // Видаляли голову

        if (toDelete->next) toDelete->next->prev = toDelete->prev;
        else tail = toDelete->prev; // Видаляли хвіст

        delete toDelete;
        count--;
    }

    size_t size() const override {
        return count;
    }

    bool isEmpty() const override {
        return count == 0;
    }

    void set(size_t index, const T& element) override {
        Node* node = getNode(index);
        if (node) {
            node->value = element;
        } else {
            throw std::out_of_range("Index out of range for set");
        }
    }
};

#endif // LIST_H