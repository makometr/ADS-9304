#include "list.h"

List::List (std::vector<std::string> text) : text(text) {
    this->head = createNode(0);
}

List::~List () {
    deleteNode(head);
}

std::ostream &operator<< (std::ostream &out, const List &list) {
    out << list.head;
    return out;
}

int List::connect (std::string number1, std::string number2) {
    int count;
    int count1 = 1, count2 = 1;
    for (char i : number1)
        if (i == '.')
            count1++;
    for (char i : number2)
        if (i == '.')
            count2++;
    if (count1 == count2) {
        count = count1;
    } else {
        std::cerr << "Error: elements are not in one sublist\n";
        return 1;
    }

    int *num1 = new int [count];
    int *num2 = new int [count];
    for (int i = 0; i < count - 1; i++) {
        int pos = number1.find('.');
        num1[i] = std::stoi(number1.substr(0, pos));
        number1.erase(0, pos + 1);
        pos = number2.find('.');
        num2[i] = std::stoi(number2.substr(0, pos));
        number2.erase(0, pos + 1);
    }
    num1[count - 1] = std::stoi(number1);
    num2[count - 1] = std::stoi(number2);

    for (int i = 0; i < count; i++) {
        if (i == count - 1) {
            if (num1[i] == num2[i]) {
                std::cerr << "Error: elements are equal\n";
                delete [] num1;
                delete [] num2;
                return 1;
            } else if (num1[i] > num2[i]) {
                int *temp = num1;
                num1 = num2;
                num2 = temp;
                break;
            } else {
                break;
            }
        }
        if (num1[i] != num2[i]) {
            std::cerr << "Error: elements are not in one sublist\n";
            delete [] num1;
            delete [] num2;
            return 1;
        }
    }

    Node *node1 = findNode(head, num1, count, 0);
    Node *node2 = findNode(head, num2, count, 0);
    if (node1 == nullptr || node2 == nullptr) {
        std::cerr << "Error: no element with such number\n";
        delete [] num1;
        delete [] num2;
        return 0;
    }

    if (std::holds_alternative<Node *>(node2->data)) {
        if (std::holds_alternative<Node *>(node1->data)) {
            Node *temp = std::get<Node *>(node1->data);
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = std::get<Node *>(node2->data);
        } else {
            node1->data = std::get<Node *>(node2->data);
        }
    } else {
        if (std::holds_alternative<std::string>(node1->data)) {
            std::string str1, str2;
            str1 = std::get<std::string>(node1->data);
            str2 = std::get<std::string>(node2->data);
            node1->data = str1.erase(str1.size() - 2, 2) + ". " + str2.erase(0, 1);
        }
    }
    node1->name += " - " + node2->name;

    Node *prev = nullptr;
    int *prevNum = new int [count];
    for (int i = 0; i < count; i++)
        prevNum[i] = num2[i];
    for (int i = num2[count - 1] - 1; i >= 0; i--) {
        prevNum[count - 1] = i;
        if ((prev = findNode(this->head, prevNum, count, 0)) != nullptr)
            break;
    }
    prev->next = node2->next;
    delete [] prevNum;
    delete node2;

    int *num = new int [count];
    for (int i = 0; i < count; i++)
        num[i] = 0;
    changeNum(this->head, num, 1);
    delete [] num;

    delete [] num1;
    delete [] num2;
    return 0;
}

Node *List::createNode (unsigned int n) {
    unsigned int pos1 = text[n].find(' '), pos2 = 0;
    std::string num = text[n].substr(0, pos1), name, str;

    if (text[n].find('\"') != std::string::npos) {
        pos2 = text[n].find('\"');
        name = text[n].substr(pos1 + 1, pos2 - pos1 - 2);
        str = text[n].substr(pos2, text[n].size());
    } else {
        name = text[n].substr(pos1 + 1, text[n].size());
        str = "";
    }

    if (n == text.size() - 1) {
        return new Node(num, name, str, nullptr);
    } else {
        int curCount = 0;
        for (char i : num)
            if (i == '.')
                curCount++;
        int nextCount = 0;
        for (char i : text[n + 1].substr(0, text[n + 1].find(' ')))
            if (i == '.')
                nextCount++;

        if (nextCount > curCount) { // node
            unsigned int next = 0;
            bool flag = false;
            for (unsigned int j = n + 1; j < text.size(); j++) {
                int jCount = 0;
                for (char i : text[j].substr(0, text[j].find(' ')))
                    if (i == '.')
                        jCount++;
                if (jCount == curCount) {
                    flag = true;
                    next = j;
                    break;
                }
                if (jCount < curCount) {
                    break;
                }
            }

            if (flag) {
                return new Node(num, name, createNode(n + 1), createNode(next));
            } else {
                return new Node(num, name, createNode(n + 1), nullptr);
            }
        } else { // atom
            if (nextCount < curCount)
                return new Node(num, name, str, nullptr);
            else
                return new Node(num, name, str, createNode(n + 1));
        }
    }
}

void List::deleteNode (Node *cur) {
    if (cur == nullptr)
        return;
    if (std::holds_alternative<Node *>(cur->data))
        deleteNode (std::get<Node *>(cur->data));
    deleteNode (cur->next);
    delete cur;
}

Node *List::findNode (Node *node, int *num, int count, int n) {
    while (node->num[n] != num[n]) {
        node = node->next;
        if (node == nullptr)
            return nullptr;
    }

    if (n < count - 1)
        if (std::holds_alternative<Node *>(node->data))
            node = findNode(std::get<Node *>(node->data), num, count, n + 1);
        else
            return nullptr;
    else
        return node;

    return node;
}

void List::changeNum (Node *cur, int *num, int count) {
    for (int i = 0; i < count; i++)
        cur->num[i] = num[i];
    if (std::holds_alternative<Node *>(cur->data)) {
        num[count] = 0;
        changeNum(std::get<Node *>(cur->data), num, count + 1);
        num[count] = 0;
    }
    if (cur->next != nullptr) {
        num[count - 1]++;
        changeNum(cur->next, num, count);
    }
}
