// Copyright 2016 Pronina Maria
#include <gtest/gtest.h>
#include <stdexcept>

#include "TODOitem.h"
#include <TODOlist.h>
#include <TODOapp.h>
#include <vector>
using ::testing::internal::RE;
using std::vector;
using std::string;
class TODOappTest : public ::testing::Test {
 protected:
    // virtual void SetUp() {}
    void ActWithExistingFile(vector<string> args_) {
        vector<const char*> options;
        TODOlist list;
        TODOitem temp;

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

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

 private:
    TODOapp app_;
    string output_;
};
TEST_F(TODOappTest, Can_Print_Help_With_Empty_Argumens) {
    vector<string> args = {};
    Act(args);
    Assert("This is a todo list application.*");
}
TEST_F(TODOappTest, Can_Not_Add_With_Wrong_Arguments_Count) {
    vector<string> args = {"add", ""};
    Act(args);
    Assert("ERROR: Wrong arguments count for item operation.*");
}
TEST_F(TODOappTest, Can_Not_Delete_With_Wrong_Arguments_Count) {
    vector<string> args = { "delete", "" };
    Act(args);
    Assert("ERROR: Wrong arguments count for item operation.*");
}
TEST_F(TODOappTest, Can_Not_Print_Item_With_Wrong_Arguments_Count) {
    vector<string> args = { "print_item", "" };
    Act(args);
    Assert("ERROR: Wrong arguments count for item operation.*");
}
TEST_F(TODOappTest, Can_Not_Print_File_With_Wrong_Arguments_Count) {
    vector<string> args = { "print_all" };
    Act(args);
    Assert("ERROR: Wrong arguments count for file operation.*");
}
TEST_F(TODOappTest, Can_Not_Add_With_Wrong_File_Name) {
    vector<string> args = { "add", "", "t" };
    Act(args);
    Assert("Can not open file .*");
}
TEST_F(TODOappTest, Can_Not_Delete_With_Wrong_File_Name) {
    vector<string> args = { "delete", "", "t" };
    Act(args);
    Assert("Can not open file .*");
}
TEST_F(TODOappTest, Can_Not_Print_Item_With_Wrong_File_Name) {
    vector<string> args = { "print_item", "", "t" };
    Act(args);
    Assert("Can not open file .*");
}
TEST_F(TODOappTest, Can_Not_Print_With_Wrong_File_Name) {
    vector<string> args = { "print_all", "" };
    Act(args);
    Assert("Can not open file .*");
}
TEST_F(TODOappTest, Can_Not_Print_Priority_With_Wrong_File_Name) {
    vector<string> args = { "print_priority", "-1" };
    Act(args);
    Assert("Can not open file .*");
}
TEST_F(TODOappTest, Can_Print_All) {
    vector<string> args = { "print_all", "test.txt" };
    ActWithExistingFile(args);
    Assert("abc 1\ndef 2\ngik 1\n");
}
TEST_F(TODOappTest, Can_Print_Item) {
    vector<string> args = { "print_item", "test.txt", "def" };
    ActWithExistingFile(args);
    Assert("def Priority: 2\n");
}
TEST_F(TODOappTest, Can_Print_Item_With_Text) {
    vector<string> args = { "print_item", "test.txt", "abc" };
    ActWithExistingFile(args);
    Assert("abc Priority: 1\nabc text\n");
}
TEST_F(TODOappTest, Can_Not_Print_Non_Existing_Item) {
    vector<string> args = { "print_item", "test.txt", "xyz" };
    ActWithExistingFile(args);
    Assert("Item with this title does not exist!.*");
}
TEST_F(TODOappTest, Can_Add_Item) {
    vector<string> args = { "add", "test.txt", "xyz" };
    ActWithExistingFile(args);
    Assert("Item has been added.*");
}
TEST_F(TODOappTest, Can_Add_Item_With_Params) {
    vector<string> args = { "add_params", "test.txt", "xyz", "5", "text" };
    ActWithExistingFile(args);
    Assert("Item has been added.*");
}
TEST_F(TODOappTest, Can_Not_Add_Item_With_Not_Number_Priority) {
    vector<string> args = { "add_params", "test.txt", "xyz", "abc", "text" };
    ActWithExistingFile(args);
    Assert("Can not add item .*");
}
TEST_F(TODOappTest, Can_Not_Add_Item_With_Negative_Priority) {
    vector<string> args = { "add_params", "test.txt", "xyz", "-5", "text" };
    ActWithExistingFile(args);
    Assert("Can not add item .*");
}
TEST_F(TODOappTest, Can_Not_Add_With_Params_Existing_Item) {
    vector<string> args = { "add_params", "test.txt", "abc", "1", "text" };
    ActWithExistingFile(args);
    Assert("Can not add item .*");
}
TEST_F(TODOappTest, Can_Not_Add_Existing_Item) {
    vector<string> args = { "add", "test.txt", "abc"};
    ActWithExistingFile(args);
    Assert("Can not add item .*");
}
TEST_F(TODOappTest, Can_Create) {
    vector<string> args = { "create", "test1.txt"};
    Act(args);
    Assert("File \"test1.txt\"has been created.*");
}
TEST_F(TODOappTest, Can_Delete_Item) {
    vector<string> args = { "delete", "test.txt", "abc" };
    Act(args);
    Assert("Item has been deleted.*");
}
TEST_F(TODOappTest, Can_Not_Delete_Non_Existing_Item) {
    vector<string> args = { "delete", "test.txt", "xyz" };
    Act(args);
    Assert("Could not delete item.*");
}
TEST_F(TODOappTest, Can_Print_Priority) {
    vector<string> args = { "print_priority", "test.txt", "1" };
    ActWithExistingFile(args);
    Assert("abc\nabc text\ngik\n");
}
TEST_F(TODOappTest, Can_Print_Non_Existing_Priority) {
    vector<string> args = { "print_priority", "test.txt", "4" };
    ActWithExistingFile(args);
    Assert("List does not contains items with this priority");
}
TEST_F(TODOappTest, Can_Print_Negative_Priority) {
    vector<string> args = { "print_priority", "test.txt", "-4" };
    ActWithExistingFile(args);
    Assert("List does not contains items with this priority");
}
TEST_F(TODOappTest, Can_Not_Print_Non_Number_Priority) {
    vector<string> args = { "print_priority", "test.txt", "abc" };
    ActWithExistingFile(args);
    Assert("Error : wrong priority");
}
