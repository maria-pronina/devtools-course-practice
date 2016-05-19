// Copyright 2016 Podchischaeva Mary, Pronina Mary

#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>

#include "include/todo_list.h"

using std::vector;
using std::out_of_range;
using std::runtime_error;

TEST(TodoList, Can_Create) {
    // Arrange
    TodoList* list;

    // Act
    list = new TodoList();

    // Assert
    EXPECT_NE(nullptr, list);

    // Free Memory
    delete list;
}

TEST(TodoList, Can_Add_By_Item) {
    // Arrange
    TodoItem item;
    TodoList list;

    item.setTitle("abc");

    // Act
    list.addItem(item);

    // Assert
    EXPECT_NE(-1, list.search("abc"));
}

TEST(TodoList, Throw_When_Add_Existing_Title_By_Item) {
    // Arrange
    TodoItem item1;
    TodoItem item2;
    TodoList list;

    item1.setTitle("abc");
    item2.setTitle("abc");

    // Act
    list.addItem(item1);

    // Assert
    EXPECT_THROW(list.addItem(item2), runtime_error);
}

TEST(TodoList, Can_Add_By_Parameters) {
    // Arrange
    TodoList list;

    // Act
    list.addItem("abc", 2);

    // Assert
    EXPECT_NE(-1, list.search("abc"));
}

TEST(TodoList, Throw_When_Add_Existing_Title_By_Parameters) {
    // Arrange
    TodoList list;

    // Act
    list.addItem("abc");

    // Assert
    EXPECT_THROW(list.addItem("abc"), runtime_error);
}

TEST(TodoList, Can_Get_Size) {
    // Arrange
    TodoList list;

    // Act
    list.addItem("abc");

    // Assert
    EXPECT_EQ(1, list.size());
}

TEST(TodoList, Can_Get_Item) {
    // Arrange
    TodoList list;

    // Act
    list.addItem("abc");
    list.addItem("defg");
    list.addItem("higk");

    // Assert
    EXPECT_EQ(list.getItem(1).getTitle(), "defg");
}

TEST(TodoList, Throws_When_Get_By_Invalid_Pos) {
    // Arrange
    TodoList list;

    // Act & Assert
    EXPECT_THROW(list.getItem(100500), out_of_range);
}

TEST(TodoList, Can_Get_All) {
    // Arrange
    TodoList list;
    vector<TodoItem> v;
    TodoItem temp;

    // Act
    temp.setTitle("abc");
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("gik");
    list.addItem(temp);
    v.push_back(temp);

    // Assert
    EXPECT_EQ(list.getAll(), v);
}

TEST(TodoList, Can_Get_By_Priority) {
    // Arrange
    TodoList list;
    vector<TodoItem> v;
    TodoItem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    list.addItem(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    // Assert
    EXPECT_EQ(list.getByPriority(1), v);
}

TEST(TodoList, Can_Save_Load) {
    // Arrange
    TodoList listForSave, listForLoad;
    vector<TodoItem> v;
    TodoItem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    listForSave.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    listForSave.addItem(temp);
    v.push_back(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    listForSave.addItem(temp);
    v.push_back(temp);

    listForSave.save("todo.list");
    listForLoad.load("todo.list");

    // Assert
    EXPECT_EQ(listForLoad.getAll(), v);
}
TEST(TodoList, Can_Not_Load_From_Non_Existing_File) {
    // Arrange
    TodoList listForLoad;
    // Act and Assert
    EXPECT_THROW(listForLoad.load("todo1.list"), std::runtime_error);
}
TEST(TodoList, Can_Not_Load_From_File_With_Empty_Name) {
    // Arrange
    TodoList listForLoad;
    // Act and Assert
    EXPECT_THROW(listForLoad.load(""), std::runtime_error);
}
TEST(TodoList, Can_Delete_By_Pos) {
    // Arrange
    TodoList list;
    vector<TodoItem> v;
    TodoItem temp;

    // Act
    temp.setTitle("abc");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    temp.setTitle("def");
    temp.setPriority(2);
    list.addItem(temp);

    temp.setTitle("gik");
    temp.setPriority(1);
    list.addItem(temp);
    v.push_back(temp);

    list.deleteItem(1);

    // Assert
    EXPECT_EQ(list.getAll(), v);
}

TEST(TodoList, Throws_When_Delete_By_Invalid_Pos) {
    // Arrange
    TodoList list;

    // Act
    list.addItem("abc");

    // Act & Assert
    EXPECT_THROW(list.deleteItem(100500), out_of_range);
}

TEST(TodoList, Can_Sort_By_Priority) {
    // Arrange
    TodoList list;
    TodoItem temp1;
    TodoItem temp2;
    vector<TodoItem> v;

    // Act
    temp1.setTitle("abc");
    temp1.setPriority(0);

    temp2.setTitle("def");
    temp2.setPriority(5);

    list.addItem(temp2);
    list.addItem(temp1);
    v.push_back(temp1);
    v.push_back(temp2);

    // Assert
    EXPECT_EQ(list.sortByPriority(), v);
}
