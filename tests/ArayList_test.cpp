#include "gtest/gtest.h"
#include "../List.h" // Підключаємо наш List.h

TEST(ArrayListTest, HandlesBasicOperations) {

ArrayList<int> list;

ASSERT_EQ(list.size(), 0);
ASSERT_TRUE(list.isEmpty());

//додаємо перший елемент
list.add(10);
ASSERT_EQ(list.size(), 1);
ASSERT_FALSE(list.isEmpty());
ASSERT_EQ(list.get(0), 10);

//додаємо другий елемент
list.add(20);
ASSERT_EQ(list.size(), 2);
ASSERT_EQ(list.get(1), 20);

//перевіряємо метод swap
list.swap(0, 1);
ASSERT_EQ(list.get(0), 20);
ASSERT_EQ(list.get(1), 10);

//видаляємо перший елемент
list.remove(0);
ASSERT_EQ(list.size(), 1);
ASSERT_EQ(list.get(0), 10); // Тепер на першому місці 10
}

//ще один тест, який перевіряє виняткові ситуації
TEST(ArrayListTest, ThrowsExceptionOnOutOfBounds) {
ArrayList<int> list;
list.add(5);

//перевіряємо, що спроба доступу за неіснуючим індексом
//уидає виключення типу std::out_of_range
ASSERT_THROW(list.get(1), std::out_of_range);
ASSERT_THROW(list.remove(10), std::out_of_range);
ASSERT_THROW(list.set(5, 100), std::out_of_range);
}