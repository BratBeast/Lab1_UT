// TextEntities.h

#ifndef TEXT_ENTITIES_H
#define TEXT_ENTITIES_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

//Level 1: базовий абстрактний клас
class TextEntity {
public:
    virtual ~TextEntity() = default;
    virtual std::string getText() const = 0;
    virtual size_t getCharCount() const = 0;
    virtual void print() const {
        std::cout << getText();
    }
};

//level 2: новий проміжний абстрактний клас для контейнерів
class CompositeTextEntity : public TextEntity {
protected:
    std::vector<std::unique_ptr<TextEntity>> children;
public:
    // Тепер цей метод буде спільним для всіх контейнерів
    void add(std::unique_ptr<TextEntity> entity) {
        children.push_back(std::move(entity));
    }
};

//level 3: конкретні класи
class Sentence : public TextEntity {
private:
    std::string text;
public:
    explicit Sentence(std::string s) : text(std::move(s)) {}
    std::string getText() const override { return text; }
    size_t getCharCount() const override { return text.length(); }
};

//Paragraph ТЕПЕР НАСЛІДУЄТЬСЯ ВІД CompositeTextEntity
class Paragraph : public CompositeTextEntity {
public:
    std::string getText() const override {
        std::string result;
        for (const auto& child : children) {
            result += child->getText() + " ";
        }
        return result;
    }

    size_t getCharCount() const override {
        size_t count = 0;
        for (const auto& child : children) {
            count += child->getCharCount();
        }
        return count;
    }

    void print() const override {
        std::cout << "    " << getText() << std::endl;
    }
};

class Document : public CompositeTextEntity {
private:
    std::string title;
public:
    explicit Document(std::string docTitle) : title(std::move(docTitle)) {}

    const std::vector<std::unique_ptr<TextEntity>>& getEntities() const {
        return children;
    }

    void addEntity(std::unique_ptr<TextEntity> entity) {
        add(std::move(entity));
    }
    
    std::string getText() const override { return title; }
    size_t getCharCount() const override { return title.length(); }

    void print() const override {
        std::cout << "--- Document: " << title << " ---" << std::endl;
        for(const auto& entity : children) {
            entity->print();
            std::cout << std::endl;
        }
        std::cout << "--- End of Document ---" << std::endl;
    }
};

#endif // TEXT_ENTITIES_H