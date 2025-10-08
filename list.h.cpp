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

#endif // LIST_H