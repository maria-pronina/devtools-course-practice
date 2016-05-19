// Copyright 2016 Pronina Maria
#include "include/todo_app.h"
#include <map>
#include <sstream>
#include <string>
#include "include/todo_list.h"
const std::map<std::string, Operations> kOperations {
    {"add", Operations::ADD},
    {"add_params", Operations::ADD_EXPAND},
    {"create", Operations::CREATE},
    {"print_item", Operations::PRINT},
    {"delete", Operations::DELETE},
    {"print_all", Operations::PRINT_ALL},
    {"print_priority", Operations::PRIORITY}
};
TodoApp::TodoApp() : message_("") {}
void TodoApp::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
        "This is a todo list application.\n\n" +
        "Please provide arguments in the following format:\n\n" +

        "1.  $ " + appname + " <file_operation> <file_name>\n\n " +
        "2. $ " + appname + " <item_operation> <file_name> <item_title>\n\n " +
        "3. $ " + appname + " add_params <file_name> <item_title>"
                +" <item_text> <item_priority>\n\n " +
        "4. $ " + appname + " print_priority <file_name> <item_priority> \n\n "
        "Where <file_operation> is one of 'print_all', 'create', " +
        "<item_operation> is one of 'add', 'delete', 'print_item' " +
        "<file_name> is a name of todo-list file to operate with, " +
        "<item_title> is a title of list element " +
        "<item_text> is a description for new list element " +
        "<item_priority> is a priority of list elements \n ";
}
bool TodoApp::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc >= 7) {
        help(argv[0], "ERROR: Too much arguments.\n\n");
        return false;
    }
    return true;
}
bool TodoApp::validateArguments(int argc, const char** argv, Operations op) {
    switch (op) {
    case Operations::ERROR:
        help(argv[0],
            "ERROR: Wrong operation name.\n\n");
        return false;
        break;
    case Operations::ADD:
        if (argc != 4) {
            help(argv[0],
                "ERROR: Wrong arguments count for add operation.\n\n");
            return false;
        }
        break;
    case Operations::ADD_EXPAND:
        if (argc != 6) {
            help(argv[0],
                "ERROR: Wrong arguments count for add_params operation.\n\n");
            return false;
        }
        break;
    case Operations::CREATE:
        if (argc != 3) {
            help(argv[0],
                "ERROR: Wrong arguments count for create operation.\n\n");
            return false;
        }
        break;
    case Operations::DELETE:
        if (argc != 4) {
            help(argv[0],
                "ERROR: Wrong arguments count for delete operation.\n\n");
            return false;
        }
        break;
    case Operations::PRINT:
        if (argc != 4) {
            help(argv[0],
             "ERROR: Wrong arguments count for print_item operation.\n\n");
            return false;
        }
        break;
    case Operations::PRINT_ALL:
        if (argc != 3) {
            help(argv[0],
             "ERROR: Wrong arguments count for print_all operation.\n\n");
            return false;
        }
        break;
    case Operations::PRIORITY:
        if (argc != 4) {
            help(argv[0],
             "ERROR: Wrong arguments count for print_priority operation.\n\n");
            return false;
        }
        break;
    }
    return true;
}
Operations TodoApp::parseOperation(std::string operation) {
    auto it = kOperations.find(operation);
    if (it == kOperations.end())
        return Operations::ERROR;
    return (*it).second;
}

std::string TodoApp::operator()(int argc, const char** argv) {
    Arguments args;
    TodoList todo;
    if (!validateNumberOfArguments(argc, argv))
        return message_;
    args.operation = parseOperation(argv[1]);
    if (!validateArguments(argc, argv, args.operation)) {
        return message_;
    }
    args.fileName = argv[2];
    std::ostringstream stream;
    if (args.operation != Operations::CREATE) {
        try {
            todo.load(args.fileName);
        }
        catch (std::runtime_error) {
            stream << "Can not open file " << args.fileName << std::endl;
            message_ = stream.str();
            return message_;
        }
    }
    switch (args.operation) {
    case Operations::ADD:
        args.itemName = argv[3];
        stream << "Trying to add item \""
         << args.itemName <<"\"..." << std::endl;
        try {
            todo.addItem(args.itemName);
            todo.save(args.fileName);
            stream << "Item has been added." << std::endl;
        } catch(std::runtime_error) {
            stream << "Can not add item " <<
                        "- item with this title already existed!" << std::endl;
        }
        break;
     case Operations::ADD_EXPAND:
         args.itemName = argv[3];
         args.newText = argv[5];
        stream << "Trying to add item \""
        << args.itemName <<"\"..." << std::endl;
        try {
            try {
                args.priority = std::stoi(argv[5]);
            }
            catch (std::exception const & e) {
                stream << "Can not add item " <<
                    "- invalid item parameters!" << std::endl;
                message_ = stream.str();
                return message_;
            }
            todo.addItem(args.itemName, args.priority, args.newText);
            todo.save(args.fileName);
            stream << "Item has been added." << std::endl;
        } catch(std::runtime_error) {
            stream << "Can not add item " <<
                        " - item with this title already existed!" << std::endl;
        } catch(std::invalid_argument) {
            stream << "Can not add item " <<
                        "- invalid item parameters!" << std::endl;
        }
        break;
     case Operations::CREATE:
         stream << "Trying to create file \"" << args.fileName
                << "\"..." << std::endl;
         todo.save(args.fileName);
         stream << "File \"" << args.fileName
          << "\"has been created" << std::endl;
         break;
    case Operations::DELETE:
        args.itemName = argv[3];
        stream << "Trying to delete item \""
        << args.itemName << "\"..." << std::endl;
        try {
            todo.deleteItem(todo.search(args.itemName));
            todo.save(args.fileName);
            stream << "Item has been deleted." << std::endl;
        }
        catch (std::out_of_range) {
            stream << "Could not delete item" <<
                    " - item with this title does not exist!" << std::endl;
        }
    break;
    case Operations::PRINT: {
        args.itemName = argv[3];
        int index_of_item = todo.search(args.itemName);
        if (index_of_item == -1) {
            stream << "Item with this title does not exist!" << std::endl;
            break;
        }
        TodoItem item = todo.getItem(index_of_item);
        stream << item.getTitle() << " Priority: "
            << item.getPriority() << std::endl;
        stream << item.getText() << std::endl;
    }
    break;
    case Operations::PRINT_ALL: {
        auto items = todo.getAll();
        for (auto it = items.begin(); it != items.end(); ++it) {
            stream << (*it).getTitle() << " "
                << (*it).getPriority() << std::endl;
        }
    }
    break;
    case Operations::PRIORITY: {
        try {
            args.priority = std::stoi(argv[3]);
        }
        catch (std::exception const & e) {
            stream << "Error : wrong priority" << std::endl;
            break;
        }
        auto priority_items = todo.getByPriority(args.priority);
        if (priority_items.size() == 0) {
            stream << "List does not contains items with this priority"
                << std::endl;
        } else {
            for (auto it = priority_items.begin(); it != priority_items.end();
                ++it) {
                stream << (*it).getTitle() << std::endl;
                stream << (*it).getText() << std::endl;
            }
        }
    }
    break;
    case Operations::ERROR: break;
    default: break;
    }
    message_ = stream.str();
    return message_;
}
