#pragma once

#include <memory>



class Node;

class List{
    std::shared_ptr<Node> firstElement;
    void createList(std::string structList);
    void checkValid(std::string structList);

public:
    List(std::string structList);
    std::shared_ptr<Node> getFirstElement();
    void revers();
    void read();
};
