#include "List_Hier.h"
#include <iostream>

int main() {
    std::string s_elem;
    std::string s_cal;
    std::getline(std::cin, s_cal);
    std::getline(std::cin, s_elem);
    try {
        List_Hier list_cal(s_cal);
        List_Hier list_elem(s_elem);
        std::cout << list_cal.call_cal(list_elem);
    }
    catch (const char* ex) {
        std::cout << ex;
    }
    return 0;
} 