#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include "TextEntities.h"
#include "List.h"
#include "SortingAlgorithms.h"
#include <memory>

using SortableEntity = TextEntity*;

class TextAnalyzer {
private:
    std::unique_ptr<SortingAlgorithm<SortableEntity>> sortStrategy;

public:
    void setSortStrategy(std::unique_ptr<SortingAlgorithm<SortableEntity>> strategy) {
        sortStrategy = std::move(strategy);
    }

    void sort(List<SortableEntity>& entityList, std::function<bool(const SortableEntity&, const SortableEntity&)> comparator) {
        if (!sortStrategy) {
            std::cerr << "Error: Sorting strategy is not set!" << std::endl;
            return;
        }
        sortStrategy->sort(entityList, comparator);
    }
};

#endif // TEXT_ANALYZER_H