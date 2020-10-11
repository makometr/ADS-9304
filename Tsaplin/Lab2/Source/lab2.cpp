#include <iostream>
#include <memory>
#include <variant>
#include <vector>
#include <stack>

template <typename base>
class Node{
    using NodePtr = std::shared_ptr<Node>;
public:
    NodePtr next;
    std::variant<NodePtr, base> value;
};

template <typename base>
std::shared_ptr<Node<base>> makeList(typename std::vector<base>::const_iterator& i){
    using NodePtr = std::shared_ptr<Node<base>>;
    NodePtr head = nullptr;
    NodePtr cur = nullptr;
    for (++i; *i != ')' ; i++){
        if ( *i == '('){
            if (head == nullptr){
                head = NodePtr (new Node<base>);
                head->value = makeList<base>(i);
                cur = head;
            }else{
                cur->next = NodePtr(new Node<base>);
                cur = cur->next;
                cur->value = makeList<base>(i);
            }
        }else {
            if (head == nullptr) {
                head = NodePtr(new Node<base>);
                head->value = *i;
                cur = head;
            } else {
                cur->next = NodePtr(new Node<base>);
                cur = cur->next;
                cur->value = *i;
            }
        }
    }
    return head;
}

bool isCorrect(const std::string& str){
    std::stack<char> Stack;
    if (str[0] != '('){
        return false;
    }
    for (char i : str){
        if (i == '('){
            Stack.push(i);
        }
        if (i == ')'){
            if (Stack.empty()){
                return false;
            }
            Stack.pop();
        }
    }
    return Stack.empty();
}

template <typename base>
void countList(std::shared_ptr<Node<base>> head, int& k, std::shared_ptr<Node<base>>& listHead, std::shared_ptr<Node<base>>& listCur){
    using NodePtr = std::shared_ptr<Node<base>>;
    NodePtr cur = head;
    while(cur != nullptr) {
        if (std::holds_alternative<NodePtr>(cur->value)) {
            countList(std::get<NodePtr>(cur->value), k, listHead, listCur);
        } else {
            k++;
            if (listHead == nullptr){
                listHead = NodePtr(new Node<base>);
                listHead->value = std::get<char>(cur->value);
                listCur = listHead;
            }else{
                listCur->next = NodePtr(new Node<base>);
                listCur = listCur->next;
                listCur->value = std::get<char>(cur->value);
            }
        }
        cur = cur->next;
    }
}

int main()
{
    std::string listString;
    std::cin >> listString;
    if (!isCorrect(listString)){
        std::cout << "List is not correct\n";
        return 0;
    }
    std::vector<char> vec(listString.begin(),listString.end());
    std::shared_ptr<Node<char>> head = nullptr;
    auto iter = vec.cbegin();
    head = makeList<char>(iter);
    int counter = 0;
    std::shared_ptr<Node<char>> list = nullptr;
    std::shared_ptr<Node<char>> listCur = nullptr; 
    countList(head, counter, list, listCur);
    std::cout << counter << "\n";
    listCur = list;
    if (counter > 0){
    	std::cout << "[";
    	while (listCur->next != nullptr){
            std::cout << std::get<char>(listCur->value) << ", ";
            listCur = listCur->next;
    	}
        std::cout << std::get<char>(listCur->value) << "]" << std::endl;
    }else{
    	std::cout << "[]" << std::endl;
    }
    return 0;
}
