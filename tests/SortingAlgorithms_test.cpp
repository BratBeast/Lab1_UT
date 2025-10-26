#include "gtest/gtest.h"
#include "../List.h"
#include "../SortingAlgorithms.h"
#include "../TextEntities.h"
#include <memory>
#include <functional>

class SortingTest : public ::testing::Test {
protected:
    void SetUp() override {
        doc = std::make_unique<Document>("Test Document");

        auto p1 = std::make_unique<Paragraph>();
        p1->add(std::make_unique<Sentence>("This is a much longer paragraph.")); // 32
        auto p2 = std::make_unique<Paragraph>();
        p2->add(std::make_unique<Sentence>("A medium one.")); // 13
        auto p3 = std::make_unique<Paragraph>();
        p3->add(std::make_unique<Sentence>("Short paragraph.")); // 17

        doc->addEntity(std::move(p1));
        doc->addEntity(std::move(p2));
        doc->addEntity(std::move(p3));

        for (const auto& entity : doc->getEntities()) {
            listToSort.add(entity.get());
        }
    }

    // Допоміжна функція для перевірки, чи відсортований список
    bool isSorted(const List<TextEntity*>& list) {
        for (size_t i = 0; i < list.size() - 1; ++i) {
            if (list.get(i)->getCharCount() > list.get(i + 1)->getCharCount()) {
                return false;
            }
        }
        return true;
    }

    std::unique_ptr<Document> doc;
    ArrayList<TextEntity*> listToSort;
};

// --- Тепер кожен алгоритм тестується в окремому блоці TEST_F ---

TEST_F(SortingTest, QuickSort) {
QuickSort<TextEntity*> sorter;
sorter.sort(listToSort, [](auto a, auto b) { return a->getCharCount() < b->getCharCount(); });
ASSERT_TRUE(isSorted(listToSort));
}

TEST_F(SortingTest, SelectionSort) {
SelectionSort<TextEntity*> sorter;
sorter.sort(listToSort, [](auto a, auto b) { return a->getCharCount() < b->getCharCount(); });
ASSERT_TRUE(isSorted(listToSort));
}

TEST_F(SortingTest, InsertionSort) {
InsertionSort<TextEntity*> sorter;
sorter.sort(listToSort, [](auto a, auto b) { return a->getCharCount() < b->getCharCount(); });
ASSERT_TRUE(isSorted(listToSort));
}

TEST_F(SortingTest, MergeSort) {
MergeSort<TextEntity*> sorter;
sorter.sort(listToSort, [](auto a, auto b) { return a->getCharCount() < b->getCharCount(); });
ASSERT_TRUE(isSorted(listToSort));
}

TEST_F(SortingTest, HeapSort) {
HeapSort<TextEntity*> sorter;
sorter.sort(listToSort, [](auto a, auto b) { return a->getCharCount() < b->getCharCount(); });
ASSERT_TRUE(isSorted(listToSort));
}

// Окремі тести для не-порівняльних алгоритмів
TEST_F(SortingTest, BucketSort) {
BucketSort<TextEntity*> sorter;
sorter.sort(listToSort, nullptr);
ASSERT_TRUE(isSorted(listToSort));
}

TEST_F(SortingTest, RadixSort) {
RadixSort<TextEntity*> sorter;
sorter.sort(listToSort, nullptr);
ASSERT_TRUE(isSorted(listToSort));
}