#ifndef MYEXS_H
#define MYEXS_H

#include <ostream>
#include <string>

enum class ExceptionsNames
{
    ex_expr_is_wrong,
    ex_list_is_wrong,
    ex_empty_values_list,
    ex_incorrect_values_list,
    ex_argument_doesnt_exists,
    ex_unnecessary_argument,
    ex_the_value_of_the_variable_is_missing
};

class MyException
{
    std::string ex_message;

public:
    MyException(const ExceptionsNames &inputed_ex_name);
    friend std::ostream &operator<<(std::ostream &out, const MyException &obj);
};
#endif