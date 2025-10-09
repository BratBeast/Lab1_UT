#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include "TextEntities.h"
#include "List.h"
#include "SortingAlgorithms.h"
#include <memory>
#include <vector>
#include <string>

//визначаємо, що всі сортувальні операції будуть над простими вказівниками
using SortableEntity = TextEntity*;

class TextAnalyzer {
private:
    //стратегія теж працює з простими вказівниками
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

        //конвертуємо наш List в тимчасовий std::vector
        std::vector<SortableEntity> tempVector;
        for (size_t i = 0; i < entityList.size(); ++i) {
            tempVector.push_back(entityList.get(i));
        }

        //віддаємо вектор на сортування нашій стратегії
        sortStrategy->sort(tempVector, comparator);

        //очищуємо оригінальний List і заповнюємо його відсортованими даними
        while (!entityList.isEmpty()) {
            entityList.remove(0);
        }
        for (const auto& item : tempVector) {
            entityList.add(item);
        }
    }
};

#endif // TEXT_ANALYZER_H