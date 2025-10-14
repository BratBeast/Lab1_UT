#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "List.h" // Працюємо виключно з нашим List
#include <functional>
#include "TextEntities.h" // Потрібно для не-порівняльних сортувань
#include <vector> // Дозволено для створення "кошиків" у BucketSort

using SortableEntity = TextEntity*;

template <typename T>
class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;
    virtual void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) = 0;
};

// --- Алгоритми, що працюють напряму з інтерфейсом List ---

template <typename T>
class InsertionSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) override {
        for (size_t i = 1; i < list.size(); i++) {
            T key = list.get(i);
            int j = i - 1;
            while (j >= 0 && comparator(key, list.get(j))) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, key);
        }
    }
};

template <typename T>
class SelectionSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T&, const T&)> comparator) override {
        for (size_t i = 0; i < list.size() - 1; i++) {
            size_t min_idx = i;
            for (size_t j = i + 1; j < list.size(); j++) {
                if (comparator(list.get(j), list.get(min_idx))) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                list.swap(i, min_idx);
            }
        }
    }
};

template <typename T>
class QuickSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T&, const T&)> comp) override {
        if (list.size() > 1) quickSortRecursive(list, 0, list.size() - 1, comp);
    }
private:
    void quickSortRecursive(List<T>& list, int low, int high, std::function<bool(const T&, const T&)> comp) {
        if (low < high) {
            int pi = partition(list, low, high, comp);
            quickSortRecursive(list, low, pi - 1, comp);
            quickSortRecursive(list, pi + 1, high, comp);
        }
    }
    int partition(List<T>& list, int low, int high, std::function<bool(const T&, const T&)> comp) {
        T pivot = list.get(high);
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (comp(list.get(j), pivot)) list.swap(++i, j);
        }
        list.swap(i + 1, high);
        return (i + 1);
    }
};

template <typename T>
class MergeSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comp) override {
        if (list.size() <= 1) return;

        // Розділяємо на два тимчасових списки нашого типу
        ArrayList<T> left, right;
        size_t mid = list.size() / 2;
        for (size_t i = 0; i < mid; i++) left.add(list.get(i));
        for (size_t i = mid; i < list.size(); i++) right.add(list.get(i));

        // Рекурсивно сортуємо їх
        sort(left, comp);
        sort(right, comp);

        // Зливаємо відсортовані списки назад в оригінальний
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (comp(left.get(i), right.get(j))) {
                list.set(k++, left.get(i++));
            } else {
                list.set(k++, right.get(j++));
            }
        }
        while (i < left.size()) list.set(k++, left.get(i++));
        while (j < right.size()) list.set(k++, right.get(j++));
    }
};

template <typename T>
class HeapSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) override {
        // Будуємо піраміду (max heap)
        for (int i = list.size() / 2 - 1; i >= 0; i--) {
            heapify(list, list.size(), i, comparator);
        }
        // Вилучаємо елементи з піраміди
        for (int i = list.size() - 1; i > 0; i--) {
            list.swap(0, i);
            heapify(list, i, 0, comparator);
        }
    }
private:
    void heapify(List<T>& list, int n, int i, std::function<bool(const T&, const T&)> comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comp(list.get(largest), list.get(left))) largest = left;
        if (right < n && comp(list.get(largest), list.get(right))) largest = right;

        if (largest != i) {
            list.swap(i, largest);
            heapify(list, n, largest, comp);
        }
    }
};


template <typename T>
class BucketSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T&, const T&)> comparator) override {
        if (list.isEmpty()) return;
        auto getKey = [](const T& item) { return item->getCharCount(); };

        size_t maxKey = 0;
        for(size_t i = 0; i < list.size(); ++i) {
            if (getKey(list.get(i)) > maxKey) maxKey = getKey(list.get(i));
        }

        // Використовуємо std::vector для створення кошиків,
        // але самі кошики - це наш ArrayList
        std::vector<ArrayList<T>> buckets(maxKey + 1);

        for (size_t i = 0; i < list.size(); ++i) {
            buckets[getKey(list.get(i))].add(list.get(i));
        }

        size_t current = 0;
        for (auto& bucket : buckets) {
            for (size_t i = 0; i < bucket.size(); ++i) {
                list.set(current++, bucket.get(i));
            }
        }
    }
};


template <typename T>
class RadixSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T&, const T&)> comparator) override {
        if (list.isEmpty()) return;
        auto getKey = [](const T& item) { return item->getCharCount(); };

        size_t maxKey = 0;
        for(size_t i = 0; i < list.size(); ++i) {
            if (getKey(list.get(i)) > maxKey) maxKey = getKey(list.get(i));
        }

        for (int exp = 1; maxKey / exp > 0; exp *= 10) {
            countingSortForRadix(list, exp, getKey);
        }
    }
private:
    void countingSortForRadix(List<T>& list, int exp, std::function<size_t(const T&)> getKey) {
        ArrayList<T> output;
        for(size_t i = 0; i < list.size(); ++i) output.add(list.get(i)); // Потрібен тимчасовий буфер

        int count[10] = {0};

        for (size_t i = 0; i < list.size(); ++i) {
            count[(getKey(list.get(i)) / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (int i = list.size() - 1; i >= 0; i--) {
            output.set(count[(getKey(list.get(i)) / exp) % 10] - 1, list.get(i));
            count[(getKey(list.get(i)) / exp) % 10]--;
        }
        for (size_t i = 0; i < list.size(); i++) {
            list.set(i, output.get(i));
        }
    }
};

#endif // SORTING_ALGORITHMS_H