#include <iostream>
#include <variant>
#include <memory>

class Node {
    using NodePtr = std::shared_ptr<Node>;

public:
    NodePtr next{ nullptr };
    std::variant<char, NodePtr> value;
    Node() = default;
    ~Node() = default;
};

std::shared_ptr<Node> found_prefix(std::string& string, int& iterator)
{
    using NodePtr = std::shared_ptr<Node>;
    int counter = 0;
    short int arg = 3;
    NodePtr head_local = std::make_shared<Node>();
    NodePtr curr_local = head_local;
    if (!string.compare(iterator, 5, "(NOT "))
        arg = 1;
    head_local->value = string[iterator];
    while ((iterator != string.length()) && (counter < arg)) {
        if (!string.compare(iterator, 5, "(AND ") || !string.compare(iterator, 5, "(NOT ") || !string.compare(iterator, 5, "(XOR "))
            iterator += 5;
        else if (!string.compare(iterator, 4, "(OR "))
            iterator += 4;
        else if (string[iterator + 1] == ' ')
            iterator += 2;
        else
            iterator++;
        if (!string.compare(iterator, 1, "(")) {
            curr_local->next = std::make_shared<Node>();
            curr_local = curr_local->next;
            curr_local->value = found_prefix(string, iterator);
            counter++;
        }
        else {
            if ((string[iterator] >= 'a') && (string[iterator] <= 'z') || (string[iterator] == ')')) {
                curr_local->next = std::make_shared<Node>();
                curr_local = curr_local->next;
                curr_local->value = string[iterator];
                counter++;
            }
            else {
                return head_local;
            }
        }
    }
    if (string[iterator] != ')')
        iterator++;
    return head_local;
}
int main(int argc, char* argv[])
{
    std::shared_ptr<Node> head;
    int iterator = 0;
    int i = 0;
    std::string text;
    while(argv[++i]){
        text += std::string(argv[i]);
    }
    head = found_prefix(text, iterator);
    if (iterator == text.length() - 1)
        std::cout << "Success\n";
    else
        std::cout << "Error\n";
    return 0;
}
