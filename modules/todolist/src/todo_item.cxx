// Copyright 2016 Podchischaeva Mary

#include <string>
#include <stdexcept>

#include "include/todo_item.h"

using std::string;
using std::out_of_range;
using std::invalid_argument;

const int TodoItem::DEFAULT_PRIORITY_VALUE;

TodoItem::TodoItem() {
    this->priority = DEFAULT_PRIORITY_VALUE;
    this->title = "";
    this->text = "";
}

TodoItem::TodoItem(int priority_val, string title_val, string text_val) {
    if ((priority_val > MAX_PRIORITY_VALUE) ||
            (priority_val < MIN_PRIORITY_VALUE)) {
        throw invalid_argument("Invalid priority!");
    } else {
        this->priority = priority_val;
        this->title = title_val;
        this->text = text_val;
    }
}

int TodoItem::getPriority() const {
    return this->priority;
}

void TodoItem::setPriority(int value) {
    if (value >= MIN_PRIORITY_VALUE && value <= MAX_PRIORITY_VALUE) {
        this->priority = value;
    } else {
        throw invalid_argument("Invalid argument!");
    }
}

void TodoItem::setTitle(string value) {
    this->title = value;
}

string TodoItem::getTitle() const {
    return this->title;
}

void TodoItem::setText(string value) {
    this->text = value;
}

string TodoItem::getText() const {
    return this->text;
}

void TodoItem::increasePriority() {
    if (this->priority > MIN_PRIORITY_VALUE) {
        this->priority--;
    } else {
        throw out_of_range("Out of range!");
    }
}

void TodoItem::decreasePriority() {
    if (this->priority < MAX_PRIORITY_VALUE) {
        this->priority++;
    } else {
        throw out_of_range("Out of range!");
    }
}

bool TodoItem::operator==(const TodoItem &a) const {
    if (this->title != a.getTitle()) {
        return false;
    } else if (this->text != a.getText()) {
        return false;
    } else if (this->priority != a.getPriority()) {
        return false;
    } else {
        return true;
    }
}

bool TodoItem::priorityCompare(const TodoItem &l, const TodoItem &r) {
    return (l.priority < r.priority);
}

TodoItem::~TodoItem() {
}

