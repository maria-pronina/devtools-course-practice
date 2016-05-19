// Copyright 2016 Podchischaeva Mary, Pronina Mary

#include "include/todo_list.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

using std::exception;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::out_of_range;
using std::sort;
using std::runtime_error;

TodoList::TodoList() {
}

void TodoList::addItem(TodoItem value) {
    if (search(value.getTitle()) < 0) {
        this->data_.push_back(value);
    } else {
        throw runtime_error("Add item with existing title!");
    }
}

void TodoList::addItem(string title,
        int priority,
        string text) {
    TodoItem temp(priority, title, text);
    if (search(temp.getTitle()) < 0) {
        this->data_.push_back(temp);
    } else {
        throw runtime_error("Add item with existing title!");
    }
}

size_t TodoList::size() {
    return this->data_.size();
}

TodoItem TodoList::getItem(size_t pos) {
    if (pos >= data_.size()) {
        throw out_of_range("Out of range!");
    } else {
        return data_[pos];
    }
}

vector<TodoItem> TodoList::getAll() {
    return this->data_;
}

vector<TodoItem> TodoList::getByPriority(int priority) {
    vector<TodoItem> res;
    for (size_t i = 0; i < data_.size(); ++i) {
        if (data_[i].getPriority() == priority) {
            res.push_back(data_[i]);
        }
    }
    return res;
}

int TodoList::search(string title) {
    int res = -1;
    for (size_t i = 0; i < data_.size(); ++i) {
        if (data_[i].getTitle() == title) {
            res = i;
            break;
        }
    }
    return res;
}

void TodoList::save(string filename) {
    ofstream file;
    file.open(filename);
    file << data_.size() << "\n";
    for (size_t i = 0; i < data_.size(); ++i) {
        file << data_[i].getPriority() << "\n";
        file << data_[i].getTitle() << "\n";
        file << data_[i].getText() << "\n";
    }
    file.close();
}

void TodoList::load(string filename) {
    ifstream file;
    file.open(filename);
    if (file.fail())
        throw runtime_error("File with this name does not exist!");
    size_t size;
    file >> size;
    file.get();
    data_.clear();
    data_.resize(size);
    for (size_t i = 0; i < size; ++i) {
        int p;
        file >> p;
        file.get();
        string line1, line2;
        std::getline(file, line1);
        std::getline(file, line2);
        TodoItem item;
        item.setPriority(p);
        item.setTitle(line1);
        item.setText(line2);
        data_[i] = item;
    }
    file.close();
}

void TodoList::deleteItem(size_t pos) {
    if (pos >= data_.size()) {
        throw out_of_range("Out of range!");
    } else {
        data_.erase(data_.begin()+pos);
    }
}

vector<TodoItem> TodoList::sortByPriority() {
    sort(data_.begin(), data_.end(), TodoItem::priorityCompare);
    return data_;
}
