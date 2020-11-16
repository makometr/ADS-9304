#ifndef MYEXS_H
#define MYEXS_H

#include <ostream>
#include <string>
#include <stdexcept>

enum class ExceptionsNames
{
    ex_logic_error,
    ex_syntax_error,
};

class MyException : public std::runtime_error
{
    std::string ex_message;

public:
    MyException(const ExceptionsNames &inputed_ex_name, const std::string &str);
    friend std::ostream &operator<<(std::ostream &out, const MyException &obj);
};
#endif