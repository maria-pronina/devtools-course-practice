// Copyright 2016 Podchischaeva Mary

#include <gtest/gtest.h>
#include <stdexcept>

#include "include/todo_item.h"

using std::out_of_range;
using std::invalid_argument;

TEST(TodoItem, Can_Create) {
    // Arrange
    TodoItem* item;

    // Act
    item = new TodoItem();

    // Assert
    EXPECT_NE(nullptr, item);

    // Free memory
    delete item;
}

TEST(TodoItem, Can_Create_By_Parameters) {
    // Arrange
    TodoItem* item;

    // Act
    item = new TodoItem(3, "abc", "");

    // Assert
    EXPECT_NE(nullptr, item);

    // Free memory
    delete item;
}


TEST(TodoItem, Throws_When_Create_By_Invalid_Parameters) {
    // Arrange & Act & Assert
    EXPECT_THROW(TodoItem(100, "", ""), invalid_argument);
}


TEST(TodoItem, Can_Priority_Get) {
    // Arrange
    TodoItem item;

    // Act & Assert
    EXPECT_EQ(TodoItem::DEFAULT_PRIORITY_VALUE, item.getPriority());
}

TEST(TodoItem, Can_Priority_Set) {
    // Arrange
    TodoItem item;

    // Act
    item.setPriority(1);

    // Assert
    EXPECT_EQ(1, item.getPriority());
}

TEST(TodoItem, Can_Title_Get) {
    // Arrange
    TodoItem item;

    // Act & Assert
    EXPECT_EQ("", item.getTitle());
}

TEST(TodoItem, Can_Title_Set) {
    // Arrange
    TodoItem item;

    // Act
    item.setTitle("abc");

    // Assert
    EXPECT_EQ("abc", item.getTitle());
}

TEST(TodoItem, Can_Text_Get) {
    // Arrange
    TodoItem item;

    // Act & Assert
    EXPECT_EQ("", item.getText());
}

TEST(TodoItem, Can_Text_Set) {
    // Arrange
    TodoItem item;

    // Act
    item.setText("abc");

    // Assert
    EXPECT_EQ("abc", item.getText());
}

TEST(TodoItem, Can_Increase_Priority) {
    // Arrange
    TodoItem item;
    int expected_priority = TodoItem::DEFAULT_PRIORITY_VALUE - 1;

    // Act
    item.increasePriority();

    // Assert
    EXPECT_EQ(expected_priority, item.getPriority());
}

TEST(TodoItem, Can_Decrease_Priority) {
    // Arrange
    TodoItem item;
    int expected_priority = TodoItem::DEFAULT_PRIORITY_VALUE + 1;

    // Act
    item.decreasePriority();

    // Assert
    EXPECT_EQ(expected_priority, item.getPriority());
}

TEST(TodoItem, Can_Compare_Items_Title) {
    // Arrange
    TodoItem item1;
    TodoItem item2;

    // Act
    item1.setTitle("abc");
    item2.setTitle("def");

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TodoItem, Can_Compare_Items_Text) {
    // Arrange
    TodoItem item1;
    TodoItem item2;

    // Act
    item1.setText("abc");
    item2.setText("def");

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TodoItem, Can_Compare_Items_Priority) {
    // Arrange
    TodoItem item1;
    TodoItem item2;

    // Act
    item1.setPriority(1);
    item2.setPriority(2);

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TodoItem, Throws_When_Inc_Invalid_Priority) {
    // Arrange
    TodoItem item1;
    item1.setPriority(TodoItem::MIN_PRIORITY_VALUE);

    // Act & Assert
    EXPECT_THROW(item1.increasePriority(), out_of_range);
}

TEST(TodoItem, Throws_When_Dec_Invalid_Priority) {
    // Arrange
    TodoItem item1;
    item1.setPriority(TodoItem::MAX_PRIORITY_VALUE);

    // Act & Assert
    EXPECT_THROW(item1.decreasePriority(), out_of_range);
}

TEST(TodoItem, Throws_When_Set_Invalid_Priority) {
    // Arrange
    TodoItem item1;

    // Act & Assert
    EXPECT_THROW(item1.setPriority(100500), invalid_argument);
}

