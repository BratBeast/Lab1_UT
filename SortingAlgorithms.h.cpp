#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "list.h"
#include <functional>

//загальний механізм, зо дозволяє підключати нові алгоритми сортування
template <typename T>
class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;
    
    virtual void sort(List<T>& list, std::function<bool(const T& a, const T& b)> comparator) = 0;
};

#endif // SORTING_ALGORITHMS_H