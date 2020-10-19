#ifndef MYLIST_H
#define MYLIST_H

#include <variant>
#include <string>
#include "MyException.h"
#include <memory>
#include <iostream>

enum class CheckArgumentFlag
{
    Start,
    NextIsArg,
    NextIsNothing
};

class MyList;

struct Node
{
private:
    friend class MyList;
    std::variant<std::string, std::shared_ptr<MyList>> item;
    std::shared_ptr<Node> next = nullptr;
};

class MyList
{
    std::shared_ptr<Node> head = nullptr;
    static const bool isNum(const std::string_view &str);
    static const bool calculate(std::shared_ptr<Node> ptr, const MyList &listOfValues, const CheckArgumentFlag check);
    static const long long findValue(const std::string_view &str, const MyList &list);

public:
    MyList(const std::string_view &&str);
    const bool calculateLogicExpr(const MyList &listOfValues);
    void append(const Node &item);
};

#endif
