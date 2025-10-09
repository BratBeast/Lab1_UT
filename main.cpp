#include <iostream>
#include <memory>
#include <string>

#include "TextEntities.h"
#include "List.h"
#include "SortingAlgorithms.h"
#include "TextAnalyzer.h"

//допоміжна функція для виводу списку в консоль
void printEntityList(const List<TextEntity*>& list, const std::string& title) {
    std::cout << "--- " << title << " ---" << std::endl;
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << "Chars: " << list.get(i)->getCharCount() << "\t| ";
        list.get(i)->print();
    }
    std::cout << "-------------------------------------------\n" << std::endl;
}


int main() {
    // 1. Створюємо документ і наповнюємо його
    Document doc("My Document");
    auto p1 = std::make_unique<Paragraph>();
    p1->addSentence(Sentence("Short paragraph.")); // 17 chars
    auto p2 = std::make_unique<Paragraph>();
    p2->addSentence(Sentence("This is a much longer paragraph.")); // 32 chars
    auto p3 = std::make_unique<Paragraph>();
    p3->addSentence(Sentence("A medium one.")); // 13 chars

    doc.addEntity(std::move(p1));
    doc.addEntity(std::move(p2));
    doc.addEntity(std::move(p3));

    //створюємо список з простих вказівників (TextEntity*)
    ArrayList<TextEntity*> entityList;
    for (const auto& entity : doc.getEntities()) {
        entityList.add(entity.get());
    }

    printEntityList(entityList, "Initial order");

    //створюємо аналізатор
    TextAnalyzer analyzer;

    //демонстрація ВСІХ сортувань

    //сортування за допомогою QuickSort (за зростанням)
    analyzer.setSortStrategy(std::make_unique<QuickSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) {
        return a->getCharCount() < b->getCharCount();
    });
    printEntityList(entityList, "Sorted with QuickSort (Ascending)");

    //сортування за допомогою MergeSort (за спаданням)
    analyzer.setSortStrategy(std::make_unique<MergeSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) {
        return a->getCharCount() > b->getCharCount();
    });
    printEntityList(entityList, "Sorted with MergeSort (Descending)");

    //сортування за допомогою SelectionSort (за зростанням)
    analyzer.setSortStrategy(std::make_unique<SelectionSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) {
        return a->getCharCount() < b->getCharCount();
    });
    printEntityList(entityList, "Sorted with SelectionSort (Ascending)");

    //сортування за допомогою InsertionSort (за спаданням)
    analyzer.setSortStrategy(std::make_unique<InsertionSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) {
        return a->getCharCount() > b->getCharCount();
    });
    printEntityList(entityList, "Sorted with InsertionSort (Descending)");

    //сортування за допомогою HeapSort (за зростанням)
    analyzer.setSortStrategy(std::make_unique<HeapSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) {
        return a->getCharCount() < b->getCharCount();
    });
    printEntityList(entityList, "Sorted with HeapSort (Ascending)");

    //сортування за допомогою BucketSort (не-порівняльний)
    analyzer.setSortStrategy(std::make_unique<BucketSort<TextEntity*>>());
    analyzer.sort(entityList, nullptr);
    printEntityList(entityList, "Sorted with BucketSort (Ascending)");

    //сортування за допомогою RadixSort (не-порівняльний)
    analyzer.setSortStrategy(std::make_unique<RadixSort<TextEntity*>>());
    analyzer.sort(entityList, nullptr);
    printEntityList(entityList, "Sorted with RadixSort (Ascending)");


    return 0;
}