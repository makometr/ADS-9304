#include "node.h"

Node::Node (std::string number, std::string name, std::variant<std::string, Node*> data, Node *next) : name(name), data(data), next(next) {
    int count = 1;
    for (char i : number)
        if (i == '.')
            count++;
    this->num = new int [count];
    this->count = count;
    for (int i = 0; i < count - 1; i++) {
        int pos = number.find('.');
        num[i] = std::stoi(number.substr(0, pos));
        number.erase(0, pos + 1);
    }
    num[count - 1] = std::stoi(number);
}

Node::~Node () {
    delete [] this->num;
}

std::ostream &operator<< (std::ostream &out, const Node *node) {
    if (node->count > 1) {
        for (int i = 0; i < node->count - 1; i++)
            out << '\t';
    }

    if (node->count == 1) {
        out << node->num[0] << ' ';
    } else {
        for (int i = 0; i < node->count - 1; i++)
            out << node->num[i] << '.';
        out << node->num[node->count - 1] << ' ';
    }

    out << node->name << ' ';

    if (std::holds_alternative<Node *>(node->data)) {
        if (std::get<Node *>(node->data) != nullptr) {
            out << '\n' << std::get<Node *>(node->data);
        }
    } else {
        out << std::get<std::string>(node->data) << '\n';
    }

    if (node->next != nullptr)
        out << node->next;
    return out;
}
