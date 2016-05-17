// Copyright 2016 Pronina Maria
#include "include/TODOapp.h"
#include <map>
#include <sstream>
#include <string>
#include "include/TODOlist.h"
const std::map<string, ArgumentsNames> kOperations {
    {"add", ADD},
    {"add_params", ADDEXPAND},
    {"create", CREATE},
    {"print_item", PRINT},
    {"delete", DELETE},
    {"print_all", PRINTALL},
    {"print_priority", PRIORITY}
};
TODOapp::TODOapp() : message_("") {}
void TODOapp::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
          "This is a todo list application.\n\n" +
          "Please provide arguments in the following format:\n\n"+

          "  $ " + appname + " <operation> <z1_imaginary> " +
          "<z2_real> <z2_imaginary> <operation>\n\n" +

          "Where all arguments are double-precision numbers, " +
          "and <operation> is one of '+', '-', '*', '/'.\n";
}

bool TODOapp::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc >= 7) {
        help(argv[0], "ERROR: Too much arguments.\n\n");
        return false;
    }
    return true;
}
bool TODOapp::validateFileOperation(int argc, const char** argv) {
    if (argc != 3) {
        help(argv[0], "ERROR: Wrong arguments count for file operation.\n\n");
        return false;
    }
    return true;
}
bool TODOapp::validateItemOperation(int argc, const char** argv) {
    if (argc != 4) {
        help(argv[0], "ERROR: Wrong arguments count for item operation.\n\n");
        return false;
    }
    return true;
}
bool TODOapp::validateArguments(int argc, const char** argv) {
    ArgumentsNames op = parseOperation(argv[1]);
    if (op == ERROR) {
        help(argv[0], "ERROR: Wrong operation name.\n\n");
        return false;
    }
    switch (op) {
        case ADD:
            return validateItemOperation(argc, argv);
        break;
        case ADDEXPAND:
            if (argc != 6) {
                help(argv[0],
                "ERROR: Wrong arguments count for add_params operation.\n\n");
                return false;
            }
            break;
        case PRINT:
            return validateItemOperation(argc, argv);
        break;
        case DELETE:
            return validateItemOperation(argc, argv);
        break;
        case PRINTALL:
            return validateFileOperation(argc, argv);
        break;
    case ERROR: break;
    case CREATE:
        return validateFileOperation(argc, argv);
        break;
    case PRIORITY:
        return validateItemOperation(argc, argv);
        break;
    default: break;
    }
    return true;
}
ArgumentsNames TODOapp::parseOperation(string operation) {
    auto it = kOperations.find(operation);
    if (it == kOperations.end())
        return ERROR;
    return (*it).second;
}

std::string TODOapp::operator()(int argc, const char** argv) {
    Arguments args;
    ArgumentsNames names;
    string fileName;
    TODOlist todo;
    if (!validateNumberOfArguments(argc, argv)) {
        return message_;
    }
    if (!validateArguments(argc, argv)) {
        return message_;
    }
    fileName = argv[2];
    std::ostringstream stream;
    try {
        names = parseOperation(argv[1]);
    }
    catch (std::string str) {
        return str;
    }
    if (names != CREATE) {
        try {
            todo.load(fileName);
        }
        catch (std::runtime_error) {
            stream << "Can not open file " << fileName << std::endl;
            message_ = stream.str();
            return message_;
        }
    }
    switch (names) {
    case ADD:
        stream << "Trying to add item \"" << argv[3] <<"\"..." << std::endl;
        try {
            todo.addItem(argv[3]);
            todo.save(fileName);
            stream << "Item has been added." << std::endl;
        } catch(std::runtime_error) {
            stream << "Can not add item " <<
                        "- item with this title already existed!" << std::endl;
        }
        break;
     case ADDEXPAND:
        stream << "Trying to add item \"" << argv[3] <<"\"..." << std::endl;
        try {
            int priority;
            try {
                priority = std::stoi(argv[4]);
            }
            catch (std::exception const & e) {
                stream << "Can not add item " <<
                    "- invalid item parameters!" << std::endl;
                message_ = stream.str();
                return message_;
            }
            todo.addItem(argv[3], priority, argv[5]);
            todo.save(fileName);
            stream << "Item has been added." << std::endl;
        } catch(std::runtime_error) {
            stream << "Can not add item " <<
                        " - item with this title already existed!" << std::endl;
        } catch(std::invalid_argument) {
            stream << "Can not add item " <<
                        "- invalid item parameters!" << std::endl;
        }
        break;
     case CREATE:
         stream << "Trying to create file \"" << fileName
                << "\"..." << std::endl;
         todo.save(fileName);
         stream << "File \"" << fileName << "\"has been created" << std::endl;
         break;
    case DELETE:
        stream << "Trying to delete item \"" << argv[3] << "\"..." << std::endl;
        try {
            todo.deleteItem(todo.search(argv[3]));
            todo.save(fileName);
            stream << "Item has been deleted." << std::endl;
        }
        catch (std::out_of_range) {
            stream << "Could not delete item" <<
                    " - item with this title does not exist!" << std::endl;
        }
    break;
    case PRINT: {
        int index_of_item = todo.search(argv[3]);
        if (index_of_item == -1) {
            stream << "Item with this title does not exist!" << std::endl;
            break;
        }
        TODOitem item = todo.getItem(index_of_item);
        stream << item.getTitle() << " Priority: "
            << item.getPriority() << std::endl;
        stream << item.getText() << std::endl;
    }
    break;
    case PRINTALL: {
        auto items = todo.getAll();
        for (auto it = items.begin(); it != items.end(); ++it) {
            stream << (*it).getTitle() << " "
                << (*it).getPriority() << std::endl;
        }
    }
    break;
    case PRIORITY: {
        int index_of_item;
        try {
            index_of_item = std::stoi(argv[3]);
        }
        catch (std::exception const & e) {
            stream << "Error : wrong priority" << std::endl;
            break;
        }
        auto priority_items = todo.getByPriority(index_of_item);
        if (priority_items.size() == 0) {
            stream << "List does not contains items with this priority"
                << std::endl;
        }
        else {
            for (auto it = priority_items.begin(); it != priority_items.end();
                ++it) {
                stream << (*it).getTitle() << std::endl;
                stream << (*it).getText() << std::endl;
            }
        }
    }
    break;
    case ERROR: break;
    default: break;
    }
    message_ = stream.str();
    return message_;
}
