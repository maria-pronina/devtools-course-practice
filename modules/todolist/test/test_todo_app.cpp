// Copyright 2016 Pronina Maria
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <string>
#include "include/todo_item.h"
#include "include/todo_list.h"
#include "include/todo_app.h"

using ::testing::internal::RE;
using std::vector;
using std::string;
class TodoAppTest : public ::testing::Test {
 protected:
    // virtual void SetUp() {}
    void ActWithExistingFile(vector<string> args_) {
        vector<const char*> options;
        TodoList list;
        TodoItem temp;

        temp.setTitle("abc");
        temp.setPriority(1);
        temp.setText("abc text");
        list.addItem(temp);

        temp.setTitle("def");
        temp.setPriority(2);
        temp.setText("");
        list.addItem(temp);

        temp.setTitle("gik");
        temp.setPriority(1);
        list.addItem(temp);
        list.save("test.txt");

        options.push_back("appname");
        for (size_t i = 0; i < args_.size(); ++i) {
            options.push_back(args_[i].c_str());
        }

        const char** argv = &options.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Act(vector<string> args_) {
        vector<const char*> options;

        options.push_back("appname");
        for (size_t i = 0; i < args_.size(); ++i) {
            options.push_back(args_[i].c_str());
        }

        const char** argv = &options.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    ::testing::AssertionResult IsMatch(std::string output,
        std::string expected) {
        if (RE::PartialMatch(output, RE(expected)))
            return ::testing::AssertionSuccess();
        else
             return ::testing::AssertionFailure()
             << "\nOutput:\n" << output
             << "\n\nRegex:\n" << expected << "\n";
    }
    void Assert(std::string expected) {
        EXPECT_TRUE(IsMatch(output_, expected));
    }

 private:
    TodoApp app_;
    string output_;
};
TEST_F(TodoAppTest, Can_Print_Help_With_Empty_Argumens) {
    vector<string> args = {};
    Act(args);
    Assert("This is a todo list application.*");
}
TEST_F(TodoAppTest, Can_Not_Add_With_Wrong_Arguments_Count) {
    vector<string> args = {"add"};
    Act(args);
    Assert("ERROR: Wrong arguments count for add operation.*");
}
TEST_F(TodoAppTest, Can_Not_Delete_With_Wrong_Arguments_Count) {
    vector<string> args = { "delete" };
    Act(args);
    Assert("ERROR: Wrong arguments count for delete operation.*");
}
TEST_F(TodoAppTest, Can_Not_Print_Item_With_Wrong_Arguments_Count) {
    vector<string> args = { "print_item"};
    Act(args);
    Assert("ERROR: Wrong arguments count for print_item operation");
}
TEST_F(TodoAppTest, Can_Not_Print_File_With_Wrong_Arguments_Count) {
    vector<string> args = { "print_all" };
    Act(args);
    Assert("ERROR: Wrong arguments count for print_all operation");
}
TEST_F(TodoAppTest, Can_Not_Add_With_Wrong_File_Name) {
    vector<string> args = { "add", "6", "t" };
    Act(args);
    Assert("Can not open file");
}
TEST_F(TodoAppTest, Can_Not_Delete_With_Wrong_File_Name) {
    vector<string> args = { "delete", "6", "t" };
    Act(args);
    Assert("Can not open file");
}
TEST_F(TodoAppTest, Can_Not_Print_Item_With_Wrong_File_Name) {
    vector<string> args = { "print_item", "6", "t" };
    Act(args);
    Assert("Can not open file");
}
TEST_F(TodoAppTest, Can_Not_Print_With_Wrong_File_Name) {
    vector<string> args = { "print_all", "6" };
    Act(args);
    Assert("Can not open file");
}
TEST_F(TodoAppTest, Can_Not_Print_Priority_With_Wrong_File_Name) {
    vector<string> args = { "print_priority", "6", "-1"};
    Act(args);
    Assert("Can not open file");
}
TEST_F(TodoAppTest, Can_Print_All) {
    vector<string> args = { "print_all", "test.txt" };
    ActWithExistingFile(args);
    Assert("abc 1\ndef 2\ngik 1\n");
}
TEST_F(TodoAppTest, Can_Print_Item) {
    vector<string> args = { "print_item", "test.txt", "def" };
    ActWithExistingFile(args);
    Assert("def Priority: 2\n");
}
TEST_F(TodoAppTest, Can_Print_Item_With_Text) {
    vector<string> args = { "print_item", "test.txt", "abc" };
    ActWithExistingFile(args);
    Assert("abc Priority: 1\nabc text\n");
}
TEST_F(TodoAppTest, Can_Not_Print_Non_Existing_Item) {
    vector<string> args = { "print_item", "test.txt", "xyz" };
    ActWithExistingFile(args);
    Assert("Item with this title does not exist!");
}
TEST_F(TodoAppTest, Can_Add_Item) {
    vector<string> args = { "add", "test.txt", "x1yz" };
    ActWithExistingFile(args);
    Assert("Item has been added");
}
TEST_F(TodoAppTest, Can_Add_Item_With_Params) {
    vector<string> args = { "add_params", "test.txt", "xyfz", "text", "5" };
    ActWithExistingFile(args);
    Assert("Item has been added");
}
TEST_F(TodoAppTest, Can_Not_Add_Item_With_Params_With_Wrong_Count_Arguments) {
    vector<string> args = { "add_params", "test.txt", "xyfz", "text" };
    ActWithExistingFile(args);
    Assert("ERROR: Wrong arguments count for add_params operation");
}
TEST_F(TodoAppTest, Can_Not_Add_Item_With_Not_Number_Priority) {
    vector<string> args = { "add_params", "test.txt", "xyz", "abc", "text" };
    ActWithExistingFile(args);
    Assert("Can not add item");
}
TEST_F(TodoAppTest, Can_Not_Add_Item_With_Negative_Priority) {
    vector<string> args = { "add_params", "test.txt", "xyz", "-5", "text" };
    ActWithExistingFile(args);
    Assert("Can not add item");
}
TEST_F(TodoAppTest, Can_Not_Add_With_Params_Existing_Item) {
    vector<string> args = { "add_params", "test.txt", "abc", "text", "1" };
    ActWithExistingFile(args);
    Assert("Can not add item");
}
TEST_F(TodoAppTest, Can_Not_Add_With_Wrong_Priority) {
    vector<string> args = { "add_params", "test.txt", "abc", "text", "-1" };
    ActWithExistingFile(args);
    Assert("Can not add item");
}
TEST_F(TodoAppTest, Can_Not_Add_Existing_Item) {
    vector<string> args = { "add", "test.txt", "abc"};
    ActWithExistingFile(args);
    Assert("Can not add item");
}
TEST_F(TodoAppTest, Can_Create_Todo_File) {
    vector<string> args = { "create", "test1.txt"};
    Act(args);
    Assert("File \"test1.txt\"has been created.*");
}
TEST_F(TodoAppTest, Can_Not_Create_Todo_File_With_Wrong_Arguments_Count) {
    vector<string> args = { "create"};
    Act(args);
    Assert("ERROR: Wrong arguments count for create operation");
}
TEST_F(TodoAppTest, Can_Print_About_Wrong_Operation) {
    vector<string> args = { "todo", "file.txt" };
    Act(args);
    Assert("ERROR: Wrong operation name");
}
TEST_F(TodoAppTest, Can_Print_About_Too_Much_Arguments) {
    vector<string> args = { "todo", "file.txt", "todo", "todo",
                             "todo", "todo" };
    Act(args);
    Assert("ERROR: Too much arguments");
}
TEST_F(TodoAppTest, Can_Delete_Item) {
    vector<string> args = { "delete", "test.txt", "abc" };
    Act(args);
    Assert("Item has been deleted");
}
TEST_F(TodoAppTest, Can_Not_Delete_Non_Existing_Item) {
    vector<string> args = { "delete", "test.txt", "xyz" };
    Act(args);
    Assert("Could not delete item");
}
TEST_F(TodoAppTest, Can_Print_Priority) {
    vector<string> args = { "print_priority", "test.txt", "1" };
    ActWithExistingFile(args);
    Assert("abc\nabc text\ngik\n");
}
TEST_F(TodoAppTest, Can_Print_Non_Existing_Priority) {
    vector<string> args = { "print_priority", "test.txt", "4" };
    ActWithExistingFile(args);
    Assert("List does not contains items with this priority");
}
TEST_F(TodoAppTest, Can_Print_Negative_Priority) {
    vector<string> args = { "print_priority", "test.txt", "-4" };
    ActWithExistingFile(args);
    Assert("List does not contains items with this priority");
}
TEST_F(TodoAppTest, Can_Not_Print_Priority_With_Wrong_Arguments_Count) {
    vector<string> args = { "print_priority", "test.txt", "-4", "10" };
    ActWithExistingFile(args);
    Assert("ERROR: Wrong arguments count for print_priority operation");
}
TEST_F(TodoAppTest, Can_Not_Print_Non_Number_Priority) {
    vector<string> args = { "print_priority", "test.txt", "abc" };
    ActWithExistingFile(args);
    Assert("Error : wrong priority");
}
