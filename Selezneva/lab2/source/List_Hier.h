#ifndef LIST_HEIR
#define LIST_HEIR

#include <variant>
#include <string>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <memory>

class List_Hier;

class Node {
    friend class List_Hier;
    std::variant<std::string, std::shared_ptr<List_Hier>> elem;
    std::shared_ptr<Node> Next = nullptr;
};

class List_Hier
{
public:
    std::shared_ptr <Node> Head = nullptr;
    List_Hier(const std::string& str);
    int call_cal( List_Hier& List_elements);
    void App_hier(const Node& new_Node);
    int calculating(std::shared_ptr <Node> ptrNode,  List_Hier& List_elements);
    int Search_for_an_element(std::shared_ptr <Node> ptr, const std::string str);
};
#endif

