// Copyright 2016 Podchishaeva Mary, Pronina Mary
#ifndef MODULES_TODOLIST_INCLUDE_TODO_ITEM_H_
#define MODULES_TODOLIST_INCLUDE_TODO_ITEM_H_

#include <string>

using std::string;

class TodoItem {
 public:
    static const int DEFAULT_PRIORITY_VALUE = 3;
    static const int MAX_PRIORITY_VALUE = 5;
    static const int MIN_PRIORITY_VALUE = 0;

    TodoItem();
    TodoItem(int priority_val, string title_val, string text_val);

    int getPriority() const;
    void setPriority(int value);

    string getTitle() const;
    void setTitle(string value);

    string getText() const;
    void setText(string value);

    void increasePriority();
    void decreasePriority();

    bool operator==(const TodoItem &a) const;
    static bool priorityCompare(const TodoItem &l, const TodoItem &r);

 private:
    int priority_;
    string title_;
    string text_;
};

#endif  // MODULES_TODOLIST_INCLUDE_TODO_ITEM_H_
