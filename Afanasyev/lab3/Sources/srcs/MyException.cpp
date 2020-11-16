#include "../libs/MyException.h"

MyException::MyException(const ExceptionsNames &inputed_ex_name, const std::string &str) : std::runtime_error(str)
{
    switch (inputed_ex_name)
    {
        case ExceptionsNames::ex_logic_error:
            this->ex_message = "Logic Error: ";
        break;
        case ExceptionsNames::ex_syntax_error:
            this->ex_message = "Syntax Error: ";
        break;
    }
    this->ex_message += str;
}

std::ostream &operator<<(std::ostream &out, const MyException &obj)
{
    out << obj.ex_message;
    return out;
}