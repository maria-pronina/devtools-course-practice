// Copyright 2016 Pronina Maria

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "include/todo_app.h"


int main(int argc, const char** argv) {
    TodoApp app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
}
