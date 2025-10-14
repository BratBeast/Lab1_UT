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
    //створюємо документ і наповнюємо його, використовуючи нову ієрархію
    Document doc("My Final Document");
    auto p1 = std::make_unique<Paragraph>();
    p1->add(std::make_unique<Sentence>("Short paragraph."));

    auto p2 = std::make_unique<Paragraph>();
    p2->add(std::make_unique<Sentence>("This is a much longer paragraph."));

    auto p3 = std::make_unique<Paragraph>();
    p3->add(std::make_unique<Sentence>("A medium one."));

    doc.addEntity(std::move(p1));
    doc.addEntity(std::move(p2));
    doc.addEntity(std::move(p3));

    //створюємо наш низькорівневий ArrayList
    ArrayList<TextEntity*> entityList;
    for (const auto& entity : doc.getEntities()) {
        entityList.add(entity.get());
    }

    printEntityList(entityList, "Initial order");

    TextAnalyzer analyzer;

    //демонстрація всіх алгоритмів сортування

    analyzer.setSortStrategy(std::make_unique<QuickSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) { return a->getCharCount() < b->getCharCount(); });
    printEntityList(entityList, "Sorted with QuickSort (Ascending)");

    analyzer.setSortStrategy(std::make_unique<SelectionSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) { return a->getCharCount() > b->getCharCount(); });
    printEntityList(entityList, "Sorted with SelectionSort (Descending)");

    analyzer.setSortStrategy(std::make_unique<InsertionSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) { return a->getCharCount() < b->getCharCount(); });
    printEntityList(entityList, "Sorted with InsertionSort (Ascending)");

    analyzer.setSortStrategy(std::make_unique<MergeSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) { return a->getCharCount() > b->getCharCount(); });
    printEntityList(entityList, "Sorted with MergeSort (Descending)");

    analyzer.setSortStrategy(std::make_unique<HeapSort<TextEntity*>>());
    analyzer.sort(entityList, [](TextEntity* a, TextEntity* b) { return a->getCharCount() < b->getCharCount(); });
    printEntityList(entityList, "Sorted with HeapSort (Ascending)");

    analyzer.setSortStrategy(std::make_unique<BucketSort<TextEntity*>>());
    analyzer.sort(entityList, nullptr);
    printEntityList(entityList, "Sorted with BucketSort (Ascending by key)");

    analyzer.setSortStrategy(std::make_unique<RadixSort<TextEntity*>>());
    analyzer.sort(entityList, nullptr);
    printEntityList(entityList, "Sorted with RadixSort (Ascending by key)");

    return 0;
}