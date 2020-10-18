#include <iostream>
#include <stack>
#include <memory>
#include <variant>

class Node {
    using NodePtr = std::shared_ptr<Node>;
public:
    int length{};
    std::variant<std::pair<NodePtr , NodePtr>, unsigned int > value;
};

unsigned int createBK(std::string & str, long unsigned int index, std::shared_ptr<Node> bk) {
    using NodePtr = std::shared_ptr<Node>;
    std::pair<NodePtr, NodePtr> side;
    if (isdigit(str[index])) {
        bk->length = std::stoi(str.substr(index));
    }
    while (isdigit(str[index])){
        index++;
    }
    if (str[index] == ' ')
        index++;
    if (str[index] == '(') {
       NodePtr left = std::make_shared<Node>();
        side.first = left;
        bk->value = side;
        while (str[index] == '(')
            index++;
        index=createBK(str, index, std::get<std::pair<NodePtr,NodePtr>>(bk->value).first);
    }
    else {
        bk->value = std::stoi(str.substr(index));
        while (isdigit(str[index])) {
            index++;
        }
    }
    if (str[index] == ' ')
        index++;
    if (str[index] == '(') {
        NodePtr right=std::make_shared<Node>();
        side.second = right;
        bk->value = side;
        index++;
        index = createBK(str, index, std::get<std::pair<NodePtr , NodePtr>>(bk->value).second);
        if (index == str.length() - 1)
            return 0;
        else
            index++;
    }
    if (str[index] == ')') {
        index++;
        return index;
    }
    return 0;
}

bool isCorrect(const std::string& str){
    int amount=0;
    for(char i:str){
        if (isdigit(i)){
            amount++;
        }
    }
    if (amount==0){
        return false;
    }
    std::stack <char> steck;
    for (char i : str) {
        if (i == '(')
            steck.push(i);
        else if (i == ')') {
            if (steck.empty()) {
                return false;
            }
            steck.pop();
        }
        else {
            if ((i != ' ' && !isdigit(i)) || steck.empty()) {
                return false;
            }
        }
    }
    return steck.empty();
}

unsigned int W(const std::shared_ptr<Node> bk, unsigned int& count) {
    using NodePtr =std::shared_ptr<Node>;
    if (std::holds_alternative<std::pair<NodePtr, NodePtr>>(bk->value)) {
        if (std::get<std::pair<NodePtr , NodePtr>>(bk->value).first != nullptr) {
            W(std::get<std::pair<NodePtr , NodePtr>>(bk->value).first, count);
        }
    }
    if (std::holds_alternative<std::pair<NodePtr , NodePtr>>(bk->value)) {
        if (std::get<std::pair<NodePtr , NodePtr>>(bk->value).second != nullptr) {
            W(std::get<std::pair<NodePtr , NodePtr>>(bk->value).second, count);
        }
    } else {
        count += std::get<unsigned int>(bk->value);
    }

    return count;
}
int main()
{
    std::string str;
    std::getline(std::cin,str);
    if (!isCorrect(str)) {
        std::cout << "Error: incorrect value\n";
        return EXIT_FAILURE;
    }
    unsigned int count=0;
    unsigned int index =0;
    using NodePtr=std::shared_ptr<Node>;
    NodePtr bk= std::make_shared<Node>();
    bk->length=0;
    createBK(str, index, bk);
    unsigned int res=W(bk,count);
    std::cout<<res<<"\n";

    return 0;
}
