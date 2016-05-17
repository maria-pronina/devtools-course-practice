// Copyright 2016 Podchischaeva Mary

#include <string>
#include <stdexcept>

#include "TODOitem.h"

using std::string;
using std::out_of_range;
using std::invalid_argument;

const int TODOitem::DEFAULT_PRIORITY_VALUE;

TODOitem::TODOitem() {
    this->priority = DEFAULT_PRIORITY_VALUE;
    this->title = "";
    this->text = "";
}

TODOitem::TODOitem(int priority_val, string title_val, string text_val) {
    if ((priority_val > MAX_PRIORITY_VALUE) ||
            (priority_val < MIN_PRIORITY_VALUE)) {
        throw invalid_argument("Invalid priority!");
    } else {
        this->priority = priority_val;
        this->title = title_val;
        this->text = text_val;
    }
}

int TODOitem::getPriority() const {
    return this->priority;
}

void TODOitem::setPriority(int value) {
    if (value >= MIN_PRIORITY_VALUE && value <= MAX_PRIORITY_VALUE) {
        this->priority = value;
    } else {
        throw invalid_argument("Invalid argument!");
    }
}

void TODOitem::setTitle(string value) {
    this->title = value;
}

string TODOitem::getTitle() const {
    return this->title;
}

void TODOitem::setText(string value) {
    this->text = value;
}

string TODOitem::getText() const {
    return this->text;
}

void TODOitem::increasePriority() {
    if (this->priority > MIN_PRIORITY_VALUE) {
        this->priority--;
    } else {
        throw out_of_range("Out of range!");
    }
}

void TODOitem::decreasePriority() {
    if (this->priority < MAX_PRIORITY_VALUE) {
        this->priority++;
    } else {
        throw out_of_range("Out of range!");
    }
}

bool TODOitem::operator==(const TODOitem &a) const {
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

bool TODOitem::priorityCompare(const TODOitem &l, const TODOitem &r) {
    return (l.priority < r.priority);
}

TODOitem::~TODOitem() {
}

