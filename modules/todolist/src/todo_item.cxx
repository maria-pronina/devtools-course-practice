// Copyright 2016 Podchischaeva Mary, Pronina Mary

#include <string>
#include <stdexcept>

#include "include/todo_item.h"

using std::string;
using std::out_of_range;
using std::invalid_argument;

const int TodoItem::DEFAULT_PRIORITY_VALUE;

TodoItem::TodoItem() {
    this->priority_ = DEFAULT_PRIORITY_VALUE;
    this->title_ = "";
    this->text_ = "";
}

TodoItem::TodoItem(int priority_val, string title_val, string text_val) {
    if ((priority_val > MAX_PRIORITY_VALUE) ||
            (priority_val < MIN_PRIORITY_VALUE)) {
        throw invalid_argument("Invalid priority!");
    } else {
        this->priority_ = priority_val;
        this->title_ = title_val;
        this->text_ = text_val;
    }
}

int TodoItem::getPriority() const {
    return this->priority_;
}

void TodoItem::setPriority(int value) {
    if (value >= MIN_PRIORITY_VALUE && value <= MAX_PRIORITY_VALUE) {
        this->priority_ = value;
    } else {
        throw invalid_argument("Invalid argument!");
    }
}

void TodoItem::setTitle(string value) {
    this->title_ = value;
}

string TodoItem::getTitle() const {
    return this->title_;
}

void TodoItem::setText(string value) {
    this->text_ = value;
}

string TodoItem::getText() const {
    return this->text_;
}

void TodoItem::increasePriority() {
    if (this->priority_ > MIN_PRIORITY_VALUE) {
        this->priority_--;
    } else {
        throw out_of_range("Out of range!");
    }
}

void TodoItem::decreasePriority() {
    if (this->priority_ < MAX_PRIORITY_VALUE) {
        this->priority_++;
    } else {
        throw out_of_range("Out of range!");
    }
}

bool TodoItem::operator==(const TodoItem &a) const {
    if (this->title_ != a.title_) {
        return false;
    } else if (this->text_ != a.text_) {
        return false;
    } else if (this->priority_ != a.priority_) {
        return false;
    } else {
        return true;
    }
}

bool TodoItem::priorityCompare(const TodoItem &l, const TodoItem &r) {
    return (l.priority_ < r.priority_);
}
