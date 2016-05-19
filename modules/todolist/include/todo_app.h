// Copyright 2016 Pronina Maria
#ifndef MODULES_TODOLIST_INCLUDE_TODO_APP_H_
#define MODULES_TODOLIST_INCLUDE_TODO_APP_H_
#include <include/todo_list.h>
#include <string>

enum class Operations {
    ERROR, ADD, ADD_EXPAND, CREATE, DELETE,
    PRINT, PRINT_ALL, PRIORITY
};
class TodoApp {
 public:
    TodoApp();
    std::string operator()(int argc, const char** argv);

 private:
    void help(const char* appname, const char* message = "");
    bool validateNumberOfArguments(int argc, const char** argv);
    bool validateArguments(int argc, const char** argv, Operations op);
    Operations parseOperation(string operation);
    std::string message_;
    typedef struct {
        Operations operation;
        std::string fileName;
        std::string itemName;
        std::string newText;
        int priority;
    } Arguments;
};
#endif  // MODULES_TODOLIST_INCLUDE_TODO_APP_H_
