#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

bool converter (const std::string &str) {
    if (str == "TRUE")
        return true;
    return false;
}

std::string analysis (std::string str) {
    unsigned int pos1 = 0, pos2 = 0;
    unsigned int pos0 = 0, pos3 = 0;

    if (str.find('(') != std::string::npos) {
        int n = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '(') {
                if (n == 0) {
                    pos1 = i;
                }
                n++;
            } else if (str[i] == ')') {
                n--;
                if (n == 0) {
                    pos2 = i;
                    str.replace(pos1, pos2 - pos1 + 1, analysis(str.substr(pos1 + 1, pos2 - pos1 - 1)));
                    str = analysis(str);
                }
            }
        }
    } else if (str.find(" AND ") != std::string::npos) {
        pos1 = str.find(" AND ");
        pos2 = pos1 + 4;
        if (str.rfind(' ', pos1 - 1) != std::string::npos)
            pos0 = str.rfind(' ', pos1 - 1) + 1;
        else
            pos0 = 0;
        if (str.find(' ', pos2 + 1) != std::string::npos)
            pos3 = str.find(' ', pos2 + 1) - 1;
        else
            pos3 = str.size() - 1;
        
        if (converter(str.substr(pos0, pos1 - pos0)) && converter(str.substr(pos2 + 1, pos3 - pos2)))
            str.replace(pos0, pos3 - pos0 + 1, "TRUE");
        else
            str.replace(pos0, pos3 - pos0 + 1, "FALSE");
        str = analysis(str);
    } else if (str.find(" OR ") != std::string::npos) {
        pos1 = str.find(" OR ");
        pos2 = pos1 + 3;
        if (str.rfind(' ', pos1 - 1) != std::string::npos)
            pos0 = str.rfind(' ', pos1 - 1) + 1;
        else
            pos0 = 0;
        if (str.find(' ', pos2 + 1) != std::string::npos)
            pos3 = str.find(' ', pos2 + 1) - 1;
        else
            pos3 = str.size() - 1;
        
        if (converter(str.substr(pos0, pos1 - pos0)) || converter(str.substr(pos2 + 1, pos3 - pos2)))
            str.replace(pos0, pos3 - pos0 + 1, "TRUE");
        else
            str.replace(pos0, pos3 - pos0 + 1, "FALSE");
        str = analysis(str);
    }

    return str;
}

int main (int argc, char *argv[]) {
    std::string str;
    if (argc < 2) 
        getline(std::cin, str);
    else
        str.assign(argv[1]);
    std::regex target("( )+");
    str = std::regex_replace(str, target, " ");
    target = "(\\( )+";
    str = std::regex_replace(str, target, "(");
    target = "( \\))+";
    str = std::regex_replace(str, target, ")");
    if (str[0] == ' ') 
        str.erase(0, 1);
    if (str[str.size() - 1] == ' ')
        str.erase(str.size() - 1, 1);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    std::cout << str << " = " << analysis(str) << '\n';
    return 0;
}
