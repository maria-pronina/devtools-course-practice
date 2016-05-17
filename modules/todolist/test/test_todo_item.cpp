// Copyright 2016 Podchischaeva Mary

#include <gtest/gtest.h>
#include <stdexcept>

#include "TODOitem.h"

using std::out_of_range;
using std::invalid_argument;

TEST(TODOitem, Can_Create) {
    // Arrange
    TODOitem* item;

    // Act
    item = new TODOitem();

    // Assert
    EXPECT_NE(nullptr, item);

    // Free memory
    delete item;
}

TEST(TODOitem, Can_Create_By_Parameters) {
    // Arrange
    TODOitem* item;

    // Act
    item = new TODOitem(3, "abc", "");

    // Assert
    EXPECT_NE(nullptr, item);

    // Free memory
    delete item;
}


TEST(TODOitem, Throws_When_Create_By_Invalid_Parameters) {
    // Arrange & Act & Assert
    EXPECT_THROW(TODOitem(100, "", ""), invalid_argument);
}


TEST(TODOitem, Can_Priority_Get) {
    // Arrange
    TODOitem item;

    // Act & Assert
    EXPECT_EQ(TODOitem::DEFAULT_PRIORITY_VALUE, item.getPriority());
}

TEST(TODOitem, Can_Priority_Set) {
    // Arrange
    TODOitem item;

    // Act
    item.setPriority(1);

    // Assert
    EXPECT_EQ(1, item.getPriority());
}

TEST(TODOitem, Can_Title_Get) {
    // Arrange
    TODOitem item;

    // Act & Assert
    EXPECT_EQ("", item.getTitle());
}

TEST(TODOitem, Can_Title_Set) {
    // Arrange
    TODOitem item;

    // Act
    item.setTitle("abc");

    // Assert
    EXPECT_EQ("abc", item.getTitle());
}

TEST(TODOitem, Can_Text_Get) {
    // Arrange
    TODOitem item;

    // Act & Assert
    EXPECT_EQ("", item.getText());
}

TEST(TODOitem, Can_Text_Set) {
    // Arrange
    TODOitem item;

    // Act
    item.setText("abc");

    // Assert
    EXPECT_EQ("abc", item.getText());
}

TEST(TODOitem, Can_Increase_Priority) {
    // Arrange
    TODOitem item;
    int expected_priority = TODOitem::DEFAULT_PRIORITY_VALUE - 1;

    // Act
    item.increasePriority();

    // Assert
    EXPECT_EQ(expected_priority, item.getPriority());
}

TEST(TODOitem, Can_Decrease_Priority) {
    // Arrange
    TODOitem item;
    int expected_priority = TODOitem::DEFAULT_PRIORITY_VALUE + 1;

    // Act
    item.decreasePriority();

    // Assert
    EXPECT_EQ(expected_priority, item.getPriority());
}

TEST(TODOitem, Can_Compare_Items_Title) {
    // Arrange
    TODOitem item1;
    TODOitem item2;

    // Act
    item1.setTitle("abc");
    item2.setTitle("def");

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TODOitem, Can_Compare_Items_Text) {
    // Arrange
    TODOitem item1;
    TODOitem item2;

    // Act
    item1.setText("abc");
    item2.setText("def");

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TODOitem, Can_Compare_Items_Priority) {
    // Arrange
    TODOitem item1;
    TODOitem item2;

    // Act
    item1.setPriority(1);
    item2.setPriority(2);

    // Assert
    EXPECT_FALSE(item1 == item2);
}

TEST(TODOitem, Throws_When_Inc_Invalid_Priority) {
    // Arrange
    TODOitem item1;
    item1.setPriority(TODOitem::MIN_PRIORITY_VALUE);

    // Act & Assert
    EXPECT_THROW(item1.increasePriority(), out_of_range);
}

TEST(TODOitem, Throws_When_Dec_Invalid_Priority) {
    // Arrange
    TODOitem item1;
    item1.setPriority(TODOitem::MAX_PRIORITY_VALUE);

    // Act & Assert
    EXPECT_THROW(item1.decreasePriority(), out_of_range);
}

TEST(TODOitem, Throws_When_Set_Invalid_Priority) {
    // Arrange
    TODOitem item1;

    // Act & Assert
    EXPECT_THROW(item1.setPriority(100500), invalid_argument);
}

