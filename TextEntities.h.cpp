#ifndef TEXT_ENTITIES_H
#define TEXT_ENTITIES_H

#include <iostream>
#include <string>

class TextEntity {
public:
    virtual ~TextEntity() = default;

    virtual std::string getText() const = 0;

    virtual size_t getCharCount() const = 0;

    virtual void print() const {
        std::cout << getText();
    }
};

#endif // TEXT_ENTITIES_H