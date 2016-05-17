// Copyright 2016 Podchischaeva Mary

#include "TODOlist.h"
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

TODOlist::TODOlist() {
}

void TODOlist::addItem(TODOitem value) {
    if (search(value.getTitle()) < 0) {
        this->data.push_back(value);
    } else {
        throw runtime_error("Add item with existing title!");
    }
}

void TODOlist::addItem(string title,
        int priority,
        string text) {
    TODOitem temp(priority, title, text);
    if (search(temp.getTitle()) < 0) {
        this->data.push_back(temp);
    } else {
        throw runtime_error("Add item with existing title!");
    }
}

size_t TODOlist::size() {
    return this->data.size();
}

TODOitem TODOlist::getItem(size_t pos) {
    if (pos >= data.size()) {
        throw out_of_range("Out of range!");
    } else {
        return data[pos];
    }
}

vector<TODOitem> TODOlist::getAll() {
    return this->data;
}

vector<TODOitem> TODOlist::getByPriority(int priority) {
    vector<TODOitem> res;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].getPriority() == priority) {
            res.push_back(data[i]);
        }
    }
    return res;
}

int TODOlist::search(string title) {
    int res = -1;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].getTitle() == title) {
            res = i;
            break;
        }
    }
    return res;
}

void TODOlist::save(string filename) {
    ofstream file;
    file.open(filename);
    file << data.size() << "\n";
    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i].getPriority() << "\n";
        file << data[i].getTitle() << "\n";
        file << data[i].getText() << "\n";
    }
    file.close();
}

void TODOlist::load(string filename) {
    ifstream file;
    file.open(filename);
    if (file.fail())
        throw runtime_error("File with this name does not exist!");
    size_t size;
    file >> size;
    file.get();
    data.clear();
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        int p;
        file >> p;
        file.get();
        string line1, line2;
        std::getline(file, line1);
        std::getline(file, line2);
        TODOitem item;
        item.setPriority(p);
        item.setTitle(line1);
        item.setText(line2);
        data[i] = item;
    }
    file.close();
}

void TODOlist::deleteItem(size_t pos) {
    if (pos >= data.size()) {
        throw out_of_range("Out of range!");
    } else {
        data.erase(data.begin()+pos);
    }
}

vector<TODOitem> TODOlist::sortByPriority() {
    sort(data.begin(), data.end(), TODOitem::priorityCompare);
    return data;
}

TODOlist::~TODOlist() {
}
