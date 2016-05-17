// Copyright 2016 Podchishaeva Mary
#ifndef MODULES_TODOLIST_INCLUDE_TODOLIST_H_
#define MODULES_TODOLIST_INCLUDE_TODOLIST_H_

#include <vector>
#include <string>
#include "TODOitem.h"

using std::vector;

class TODOlist {
 private:
    vector<TODOitem> data;

 public:
    TODOlist();

    void addItem(TODOitem value);
    void addItem(string title,
            int priority = TODOitem::DEFAULT_PRIORITY_VALUE,
            string text = "");

    size_t size();

    TODOitem getItem(size_t pos);
    vector<TODOitem> getAll();
    vector<TODOitem> getByPriority(int priority);
    vector<TODOitem> sortByPriority();

    int search(string title);

    void save(string fileName);
    void load(string fileName);

    void deleteItem(size_t pos);

    ~TODOlist();
};

#endif  // MODULES_TODOLIST_INCLUDE_TODOLIST_H_
