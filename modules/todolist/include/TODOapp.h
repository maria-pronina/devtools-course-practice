// Copyright 2016 Pronina Maria
#ifndef MODULES_TODOLIST_INCLUDE_TODOAPP_H_
#define MODULES_TODOLIST_INCLUDE_TODOAPP_H_
#include <include/TODOlist.h>
#include <string>

enum ArgumentsNames { ERROR, ADD, ADDEXPAND, CREATE, DELETE,
                    PRINT, PRINTALL, PRIORITY};
class TODOapp {
 public:
    TODOapp();
    std::string operator()(int argc, const char** argv);

 private:
    void help(const char* appname, const char* message = "");
    bool validateNumberOfArguments(int argc, const char** argv);
    bool validateArguments(int argc, const char** argv);
    bool validateFileOperation(int argc, const char** argv);
    bool validateItemOperation(int argc, const char** argv);
    ArgumentsNames parseOperation(string operation);
    std::string message_;
    typedef struct {
        std::string operation;
        std::string fileName;
        std::string itemName;
        std::string newTitle;
        std::string newText;
        int priority;
    } Arguments;
};
#endif  // MODULES_TODOLIST_INCLUDE_TODOAPP_H_
