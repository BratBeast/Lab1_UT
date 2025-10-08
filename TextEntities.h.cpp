#ifndef TEXT_ENTITIES_H
#define TEXT_ENTITIES_H

#include <iostream>
#include <string>
#include <vector>

//абстрактний базовий клас, для представлення всіх текстових видів  
class TextEntity {
public:
    virtual ~TextEntity() = default;

    virtual std::string getText() const = 0;

    virtual size_t getCharCount() const = 0;

    virtual void print() const {
        std::cout << getText();
    }
};

//клас представлення одного речення
class Sentence : public TextEntity {
private:
    std::string text;

public:
    explicit Sentence(std::string s) : text(std::move(s)) {}

    std::string getText() const override {
        return text;
    }

    size_t getCharCount() const override {
        return text.length();
    }
};

// абзац, що складається з речень
class Paragraph : public TextEntity {
private:
    std::vector<Sentence> sentences;

public:
    void addSentence(const Sentence& sentence) {
        sentences.push_back(sentence);
    }

    std::string getText() const override {
        std::string result;
        for (const auto& s : sentences) {
            result += s.getText() + " ";
        }
        return result;
    }

    size_t getCharCount() const override {
        size_t count = 0;
        for (const auto& s : sentences) {
            count += s.getCharCount();
        }
        return count;
    }

    void print() const override {
        std::cout << "    " << getText() << std::endl; // З відступом для абзацу
    }
};

#endif // TEXT_ENTITIES_H