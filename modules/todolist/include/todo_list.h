// Copyright 2016 Podchishaeva Mary, Pronina Mary
#ifndef MODULES_TODOLIST_INCLUDE_TODO_LIST_H_
#define MODULES_TODOLIST_INCLUDE_TODO_LIST_H_

#include <vector>
#include <string>
#include "include/todo_item.h"

using std::vector;

class TodoList {
 public:
    TodoList();

    void addItem(TodoItem value);
    void addItem(string title,
        int priority = TodoItem::DEFAULT_PRIORITY_VALUE,
        string text = "");

    size_t size();

    TodoItem getItem(size_t pos);
    vector<TodoItem> getAll();
    vector<TodoItem> getByPriority(int priority);
    vector<TodoItem> sortByPriority();

    int search(string title);

    void save(string fileName);
    void load(string fileName);

    void deleteItem(size_t pos);



 private:
    vector<TodoItem> data_;
};

#endif  // MODULES_TODOLIST_INCLUDE_TODO_LIST_H_
