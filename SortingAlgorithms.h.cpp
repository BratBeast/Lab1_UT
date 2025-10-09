#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "list.h"
#include <functional>
#include <vector>
#include <algorithm>

//загальний механізм, зо дозволяє підключати нові алгоритми сортування
template <typename T>
class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;

    virtual void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) = 0;
};

//базові алгоритми сортування
template <typename T>
class InsertionSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) override {
        std::vector<T> temp;
        for (size_t i = 0; i < list.size(); ++i) temp.push_back(list.get(i));

        for (size_t i = 1; i < temp.size(); i++) {
            T key = temp[i];
            int j = i - 1;
            while (j >= 0 && comparator(key, temp[j])) {
                temp[j + 1] = temp[j];
                j = j - 1;
            }
            temp[j + 1] = key;
        }

        while (!list.isEmpty()) list.remove(0);
        for (const auto& item : temp) list.add(item);
    }
};

template <typename T>
class QuickSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) override {
        std::vector<T> temp;
        for (size_t i = 0; i < list.size(); ++i) temp.push_back(list.get(i));
        if(!temp.empty()) quickSortRecursive(temp, 0, temp.size() - 1, comparator);
        while (!list.isEmpty()) list.remove(0);
        for (const auto& item : temp) list.add(item);
    }
private:
    void quickSortRecursive(std::vector<T>& arr, int low, int high, std::function<bool(const T&, const T&)> comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortRecursive(arr, low, pi - 1, comp);
            quickSortRecursive(arr, pi + 1, high, comp);
        }
    }
    int partition(std::vector<T>& arr, int low, int high, std::function<bool(const T&, const T&)> comp) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
};

template <typename T>
class MergeSort : public SortingAlgorithm<T> {
public:
    void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) override {
        std::vector<T> temp;
        for (size_t i = 0; i < list.size(); ++i) temp.push_back(list.get(i));
        if(!temp.empty()) mergeSortRecursive(temp, 0, temp.size() - 1, comparator);
        while (!list.isEmpty()) list.remove(0);
        for (const auto& item : temp) list.add(item);
    }
private:
    void merge(std::vector<T>& arr, int l, int m, int r, std::function<bool(const T&, const T&)> comp) {
        int n1 = m - l + 1, n2 = r - m;
        std::vector<T> L(n1), R(n2);
        for(int i = 0; i < n1; i++) L[i] = arr[l + i];
        for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) arr[k++] = comp(L[i], R[j]) ? L[i++] : R[j++];
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }
    void mergeSortRecursive(std::vector<T>& arr, int l, int r, std::function<bool(const T&, const T&)> comp) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSortRecursive(arr, l, m, comp);
            mergeSortRecursive(arr, m + 1, r, comp);
            merge(arr, l, m, r, comp);
        }
    }
};

#endif // SORTING_ALGORITHMS_H