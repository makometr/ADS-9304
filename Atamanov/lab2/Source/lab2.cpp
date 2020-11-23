#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <variant>
#include <algorithm>

template <typename base>
class Node {
public:
    std::shared_ptr<Node> next{nullptr};
    std::variant<std::shared_ptr<Node>, base> value;

    std::shared_ptr<Node<base>> getList(typename base::const_iterator &begin, std::shared_ptr<Node<base>> &head) {
        std::shared_ptr<Node<base>> temp;
        base listValue;
        while (*begin != '\0') {
            if (*begin == '(') {
                if (temp == nullptr) {
                    temp = std::make_shared<Node<base>>();
                    begin++;
                    temp->value = getList(begin, head);
                } else {
                    begin++;
                    temp->value = getList(begin, head);
                }
            } else if (*begin != ')') {
                if (temp == nullptr) {
                    temp = std::make_shared<Node<base>>();
                    listValue = *begin;
                    temp->value = listValue;
                    begin++;
                    temp->next = getList(begin, head);
                } else {
                    listValue = *begin;
                    temp->value = listValue;
                    begin++;
                    temp->next = getList(begin, head);
                }
            } else {
                if (temp == nullptr) {
                    return temp;
                } else if (temp->next == nullptr && std::holds_alternative<base>(temp->value)) {
                    return temp;
                } else if (temp->next != nullptr && std::holds_alternative<base>(temp->value)) {
                    return temp;
                } else if (temp->next != nullptr && !std::holds_alternative<base>(temp->value)) {
                    return temp;
                } else {
                    if (*(++begin) == '\0')
                        return temp;
                    else
                        temp->next = getList(begin, head);
                }
            }
        }
    }

    void getDiffAtomList(std::shared_ptr<Node<base>> list, std::vector<base> &values, std::shared_ptr<Node<base>> &output, std::shared_ptr<Node<base>> &head) {
        while (list != nullptr) {
            if (std::holds_alternative<base>(list->value)) {
                if (std::find(values.begin(), values.end(), std::get<base>(list->value)) == values.end()) {
                    values.push_back(std::get<base>(list->value));
                    if (head == nullptr) {
                        head = std::make_shared<Node<base>>();
                        head->value = std::get<base>(list->value);
                        output = head;
                    } else {
                        output->next = std::make_shared<Node<base>>();
                        output = output->next;
                        output->value = std::get<base>(list->value);
                    }
                }
            } else {
                getDiffAtomList(std::get<std::shared_ptr<Node<base>>>(list->value), values, output, head);
            }
            list = list->next;
        }
    }
};

std::string getConvenientLine(std::string::iterator iter){
    std::string output;
    output.clear();
    while(*iter != '\0'){
        if(*iter != ' ')
            output.push_back(*iter);
        iter++;
    }
    return output;
}

bool isCorrect(std::string::const_iterator& begin){
    std::stack<char> Stack;
    if (*begin != '('){
        return false;
    }
    for (;*begin != '\0';begin++){
        if (*begin == '('){
            Stack.push(*begin);
        }
        if (*begin == ')'){
            if (Stack.empty()){
                return false;
            }
            Stack.pop();
        }
    }
    return Stack.empty();
}

int main(){
    std::string stringList;
    std::getline(std::cin, stringList);
    auto iterCheck = stringList.begin();
    stringList = getConvenientLine(iterCheck);
    auto iterBeg = stringList.cbegin();
    if(!isCorrect(iterBeg)){
        std::cout << "Wrong stringList format\n";
        exit(EXIT_FAILURE);
    }
	iterBeg = stringList.cbegin();
    std::shared_ptr<Node<std::string>> list;
    list = list->getList(iterBeg, list);
    std::vector<std::string> atoms;
    std::shared_ptr<Node<std::string>> atomList, atomHead;
    list->getDiffAtomList(std::get<std::shared_ptr<Node<std::string>>>(list->value), atoms, atomList, atomHead);
    atomList = atomHead;
    std::cout << "Число различных атомов: " << atoms.size() << "\n";
    std::cout << '[';
    while(atomList != nullptr){
        if(atomList -> next == nullptr){
            std::cout << std::get<std::string>(atomList->value);
            break;
        }
        std::cout << std::get<std::string>(atomList->value) << ',';
        atomList = atomList->next;
    }
    std::cout << "]\n";
    return 0;
}
