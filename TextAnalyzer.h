#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include "TextEntities.h"
#include "List.h"
#include "SortingAlgorithms.h"
#include <memory>
#include <vector>
#include <string>

using EntityPtr = std::unique_ptr<TextEntity>;

class TextAnalyzer {
private:
    std::unique_ptr<SortingAlgorithm<EntityPtr&>> sortStrategy;

public:
    void setSortStrategy(std::unique_ptr<SortingAlgorithm<EntityPtr&>> strategy) {
        sortStrategy = std::move(strategy);
    }

    void sort(List<EntityPtr&>& entityList, std::function<bool(const EntityPtr&, const EntityPtr&)> comparator) {
        if (!sortStrategy) {
            std::cerr << "Error: Sorting strategy is not set!" << std::endl;
            return;
        }
        sortStrategy->sort(entityList, comparator);
    }

    std::vector<std::string> checkImageCaptions(const Document& doc) {
        return {};
    }

    std::vector<std::string> findLongSentences(const Document& doc, size_t maxWordCount) {
        return {};
    }
};

#endif // TEXT_ANALYZER_H