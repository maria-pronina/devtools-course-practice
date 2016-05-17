// Copyright 2016 Podchishaeva Mary
#ifndef MODULES_TODOLIST_INCLUDE_TODOITEM_H_
#define MODULES_TODOLIST_INCLUDE_TODOITEM_H_

#include <string>

using std::string;

class TODOitem {
 private:
    int priority;
    string title;
    string text;

 public:
    static const int DEFAULT_PRIORITY_VALUE = 3;
    static const int MAX_PRIORITY_VALUE = 5;
    static const int MIN_PRIORITY_VALUE = 0;

    TODOitem();
    TODOitem(int priority_val, string title_val, string text_val);

    int getPriority() const;
    void setPriority(int value);

    string getTitle() const;
    void setTitle(string value);

    string getText() const;
    void setText(string value);

    void increasePriority();
    void decreasePriority();

    bool operator==(const TODOitem &a) const;
    static bool priorityCompare(const TODOitem &l, const TODOitem &r);

    ~TODOitem();
};

#endif  // MODULES_TODOLIST_INCLUDE_TODOITEM_H_
