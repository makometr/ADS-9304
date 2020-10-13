#include "../libs/MyException.h"

MyException::MyException(const ExceptionsNames &inputed_ex_name)
{
    this->ex_message = "Syntax error: ";
    switch (inputed_ex_name)
    {
    case ExceptionsNames::ex_expr_is_wrong:
        this->ex_message += "The inputted expression is wrong";
        break;
    case ExceptionsNames::ex_argument_doesnt_exists:
        this->ex_message += "One of the arguments doesn't exists";
        break;
    case ExceptionsNames::ex_empty_values_list:
        this->ex_message += "The inputted list of variable values is empty";
        break;
    case ExceptionsNames::ex_incorrect_values_list:
        this->ex_message += "The inputted list of variable values is wrong";
        break;
    case ExceptionsNames::ex_unnecessary_argument:
        this->ex_message += "One of the arguments is unnecessary";
        break;
    case ExceptionsNames::ex_the_value_of_the_variable_is_missing:
        this->ex_message += "The value of one of the variables is missing";
        break;
    case ExceptionsNames::ex_list_is_wrong:
        this->ex_message += "The list is wrong";
        break;
    }
}

std::ostream &operator<<(std::ostream &out, const MyException &obj)
{
    out << obj.ex_message;
    return out;
}