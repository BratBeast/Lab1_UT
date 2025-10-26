#include "gtest/gtest.h"
#include "../List.h" // Підключаємо наш List.h

// Тестовий набір для класу LinkedList
TEST(LinkedListTest, HandlesBasicOperations) {
// Arrange: Створюємо об'єкт для тестування
LinkedList<int> list;

// Assert: Перевіряємо початковий стан
ASSERT_EQ(list.size(), 0);
ASSERT_TRUE(list.isEmpty());

// Act & Assert: Додаємо елементи і перевіряємо
list.add(100);
list.add(200);
ASSERT_EQ(list.size(), 2);
ASSERT_EQ(list.get(0), 100);
ASSERT_EQ(list.get(1), 200);

// Act & Assert: Перевіряємо видалення
list.remove(0); // Видаляємо перший елемент (100)
ASSERT_EQ(list.size(), 1);
ASSERT_EQ(list.get(0), 200); // Тепер 200 має бути першим
}

// Тест для перевірки виняткових ситуацій (граничні випадки)
TEST(LinkedListTest, ThrowsExceptionOnOutOfBounds) {
LinkedList<std::string> list;
list.add("test");

// Assert: Перевіряємо, що спроба доступу за неіснуючим індексом
// кидає виключення типу std::out_of_range
ASSERT_THROW(list.get(5), std::out_of_range);
ASSERT_THROW(list.remove(1), std::out_of_range);
ASSERT_THROW(list.set(2, "new"), std::out_of_range);
}