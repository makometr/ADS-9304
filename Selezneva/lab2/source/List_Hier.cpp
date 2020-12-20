#include "List_Hier.h"

size_t search_the_bracket(const std::string str) {
    size_t i = 0;
    int bracket = 0;
    do {
        if (str.at(i) == '(') {
            ++bracket;
        }
        else if (str.at(i) == ')') {
            --bracket;
        }
        ++i;
    } while (bracket != 0 && i < str.size());
    if (bracket != 0) {
        return 0;
    }
    return i;

}

List_Hier::List_Hier(const std::string& str)
{
    bool is_first_bracket = true;
    size_t i = 0;
    while (i < str.size()) {
        if (str.at(i) == '(') {
            if (search_the_bracket(str) == 0 && search_the_bracket(str) != str.size()) {
                throw ("input not true\n");
            }
            if (is_first_bracket) {
                is_first_bracket = false;
                ++i;
            }
            else {
                std::shared_ptr <List_Hier> new_elem(new List_Hier(str.substr(i, str.size())));
                Node new_Node;
                new_Node.elem = new_elem;
                this->App_hier(new_Node);
                i = str.size();
            }
        }
        else if (isdigit(str.at(i)) || isalpha(str.at(i)) || str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*') {
            if (is_first_bracket) {
                throw ("input not true\n");
            }
            else {
                if (str.find("power(", i) == i) {
                    if (str.find(',', i) == str.size()) {
                        throw ("input not true\n");
                    }
                    else {
                        const std::string new_elem = str.substr(i, 5);
                        Node new_Node;
                        new_Node.elem = (std::string)new_elem;
                        this->App_hier(new_Node);
                        i = i + 6;
                        // �������� ����� �������
                        size_t comma = str.find(',', i);
                        std::shared_ptr <List_Hier> new_elem_1(new List_Hier(str.substr(i, comma - i)));
                        Node new_Node_1;
                        new_Node_1.elem = new_elem_1;
                        this->App_hier(new_Node_1);
                        // �������� ����� �������
                        size_t end_two_arg = search_the_bracket(str.substr(comma + 1, str.size()));
                        std::shared_ptr <List_Hier> new_elem_2(new List_Hier(str.substr(comma + 1, end_two_arg - comma - 2)));
                        Node new_Node_2;
                        new_Node_2.elem = new_elem_2;
                        this->App_hier(new_Node_2);
                        i = end_two_arg+1;
                    }
                }
                else {
                    size_t i_1 = i;
                    i = str.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM-+*", i + 1);
                    const std::string new_elem = str.substr(i_1, i - i_1);
                    Node new_Node;
                    new_Node.elem = (std::string)new_elem;
                    this->App_hier(new_Node);
                }
            }
        }
        else if (str.at(i) == ' ' || str.at(i) == ')' || str.at(i) == ',') {
            ++i;
        }
        else {
            throw ("input not true\n");
        }
    }
}

void List_Hier::App_hier(const Node& new_Node) {
    std::shared_ptr <Node> node = std::make_shared<Node>(new_Node);
    std::shared_ptr <Node> ptr = this->Head;
    if (this->Head != nullptr) {
        while (ptr->Next != nullptr) {
            ptr = ptr->Next;
        }
        ptr->Next = node;
    }
    else {
        this->Head = node;
    }
}
bool from_string_to_int(const std::string str) {
    size_t i = 0;
    if (str.at(0) == '-' || str.at(0) == '+') {
        ++i;
    }
    while (i < str.size()) {
        if (isdigit(str.at(i))) {
            ++i;
        }
        else {
            return false;
        }
    }
    return true;
}

int List_Hier::call_cal( List_Hier& List_elements) {
    return calculating(this->Head, List_elements);
}

int List_Hier::calculating(std::shared_ptr <Node> ptr_Node,  List_Hier& List_elements) {
    if (ptr_Node == nullptr) {
        throw ("error calculating\n");
    }
    else if (std::holds_alternative<std::string>(ptr_Node->elem)) {
        std::string str = std::get<std::string>(ptr_Node->elem);
        if (str == "+") {
            if (ptr_Node->Next == nullptr && ptr_Node->Next->Next == nullptr) {
                throw ("error calculating\n");
            }
            int first = calculating(ptr_Node->Next, List_elements);
            int second = calculating(ptr_Node->Next->Next, List_elements);
            return first + second;
        }
        else if (str == "-") {
            if (ptr_Node->Next == nullptr && ptr_Node->Next->Next == nullptr) {
                throw ("error calculating\n");
            }
            int first = calculating(ptr_Node->Next, List_elements);
            int second = calculating(ptr_Node->Next->Next, List_elements);
            return first - second;
        }
        else if (str == "*") {
            if (ptr_Node->Next == nullptr && ptr_Node->Next->Next == nullptr) {
                throw ("error calculating\n");
            }
            int first = calculating(ptr_Node->Next, List_elements);
            int second = calculating(ptr_Node->Next->Next, List_elements);
            return first * second;
        }
        else if (str == "power") {
            if (ptr_Node->Next == nullptr && ptr_Node->Next->Next == nullptr) {
                throw ("error calculating\n");
            }
            int first = calculating(ptr_Node->Next, List_elements);
            int second = calculating(ptr_Node->Next->Next, List_elements);
            return (int)pow(first, second);
        }
        else {
            if (from_string_to_int(str)) {
                if (str.at(0) == '-') {
                    std::string str_1 = str.substr(1, str.size() - 1);
                    return -atoi(str_1.c_str());
                }
                else if (str.at(0) == '+') {
                    std::string str_1 = str.substr(1, str.size() - 1);
                    return atoi(str_1.c_str());
                }
                else {
                    return atoi(str.c_str());
                }
            }
            else {
                return Search_for_an_element(List_elements.Head, str);
            }
        }
    }
    else if (std::holds_alternative<std::shared_ptr<List_Hier>>(ptr_Node->elem)) {
        return calculating(std::get< std::shared_ptr<List_Hier>>(ptr_Node->elem)->Head, List_elements);
    }
    throw ("error calculating\n");
 }

int List_Hier::Search_for_an_element(std::shared_ptr <Node> ptr, const std::string str) {
    if (ptr == nullptr) {
        throw ("list of elements is empty\n");
    }
    while (ptr != nullptr) {
        if (std::holds_alternative<std::string>(ptr->elem)) {
            std::string str_node = std::get<std::string>(ptr->elem);
            if (str_node == str) {
                std::string str_elem = std::get<std::string>(ptr->Next->elem);
                if (from_string_to_int(str_elem)) {
                    if (str_elem.at(0) == '-') {
                        std::string str_1 = str_elem.substr(1, str.size() - 1);
                        return -atoi(str_1.c_str());
                    }
                    else {
                        return atoi(str_elem.c_str());
                    }
                }
                else {
                    throw ("element is not an integer\n");
                }
            }
        }
        else if (std::holds_alternative<std::shared_ptr<List_Hier>>(ptr->elem)) {
            return Search_for_an_element(std::get< std::shared_ptr<List_Hier>>(ptr->elem)->Head, str);
        }
        ptr = ptr->Next;
    }
    throw ("element is not found\n");
}