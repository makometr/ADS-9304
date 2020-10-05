#include <iostream>
#include <cctype>
#include <string>

std::string is_expression(std::string);
bool is_iden(const std::string::iterator);
bool is_sign(const std::string::iterator);
bool is_bracketEx(std::string::iterator&);
bool is_expression(std::string::iterator&);

std::string is_expression(std::string in) {
    auto iter = in.begin();
    if(is_iden(iter) || is_bracketEx(iter)) {
        iter++;
        if(*iter) {
            return "There is more symbols than one expression\n";
        }
        return "One expression detected\n";
    }
    return "There is no expressions\n";
}

bool is_expression(std::string::iterator &iter) {
    if(is_iden(iter) || is_bracketEx(iter)) {
        return true;
    }
    return false;
}

bool is_bracketEx(std::string::iterator &iter)
{
    if(!(*iter)) {
        return false;
    }
    if(*iter != '(') {
        return false;
    }
    iter++;
    if(!(is_expression(iter))) {
        return false;
    }
    iter++;
    if(!(is_sign(iter))) {
        return false;
    }
    iter++;
    while(isspace(*iter)) iter++;
    if(!(is_expression(iter))) {
        return false;
    }
    iter++;
    if(*iter != ')') {
        return false;
    }
    return true;
}

bool is_iden (const std::string::iterator iter) {
    return std::isalpha(*iter);
}

bool is_sign (const std::string::iterator iter) {
    std::string signs = "-+*";
    for(auto it = signs.begin(); it != signs.end(); it++) {
        if(*it == *iter) {
            return true;
        }
    }
    return false;
}

int main() {
    std::string in;
    std::cout << "Enter an expression\n";
    std::cin >> in;
    std::cout << is_expression(in);
    return 0;
}