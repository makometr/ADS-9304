#include "tree.h"

Tree::Tree () {
    std::shared_ptr<Node> null = nullptr;
    root = std::make_shared<Node>(null, '\0');
    nodeArray.push_back(root);
}

std::pair<std::shared_ptr<Node>, std::string> Tree::find (char data) {
    return recursionFind(this->root, data, "");
}

std::pair<std::shared_ptr<Node>, char> Tree::find (std::string &str) {
    return recursionFind(this->root, str);
}

std::shared_ptr<Node> Tree::insert (char data) {
    std::shared_ptr<Node> null = nullptr;
    std::shared_ptr<Node> cur = std::make_shared<Node>(null, data);
    auto searchResult = recursionFind(this->root, '\0', "");
    std::shared_ptr<Node> zero = std::get<0>(searchResult);
    if (!zero->parent.lock()) {
        root = std::make_shared<Node>(zero, cur, null);
        cur->parent = root;
        zero->parent = root;
        cur->add();
    } else {
        std::shared_ptr<Node> parent = std::make_shared<Node>(zero, cur, zero->parent);
        cur->parent = parent;
        if (zero->parent.lock()->left == zero)
            zero->parent.lock()->left = parent;
        else
            zero->parent.lock()->right = parent;
        zero->parent = parent;
        cur->add();
    }

    std::vector<std::shared_ptr<Node>>::reverse_iterator iter;
    for (iter = nodeArray.rbegin(); iter != nodeArray.rend(); iter++) 
        if (std::holds_alternative<char>((*iter)->data) && (*iter)->weight == 0) {
            *iter = zero->parent.lock();
            break;
        }
    nodeArray.push_back(cur);
    nodeArray.push_back(zero);
    return cur;    
}

std::ostream &operator<< (std::ostream &out, const Tree &cur) {
    cur.root->print(out, 0);
    return out;
}

void Tree::removeSpaces (std::string &str) {
    for (int i = 0; i < str.length(); i++) 
        if (isspace(str[i])) {
            str.erase(i, 1);
            i--;
        }
}

std::string Tree::encode (std::string &str, bool isDebug) {
    Tree tree;
    std::string result = "";
    int num = 0;
    for (char symbol : str) {
        if (isDebug)
            std::cout << "Encoding \'" << symbol << "\'...\n"; 
        auto searchResult = tree.find(symbol);
        if (std::get<0>(searchResult)) {
            result += std::get<1>(searchResult);
            std::get<0>(searchResult)->add();
            if (isDebug) {
                std::cout << "\'" << symbol << "\' is in the tree. Increasing...\n\n";
                tree.root->colorPrint({std::get<0>(searchResult)}, 0); 
                std::cout << "\n\'" << symbol << "\' -> " << std::get<1>(searchResult) << '\n';
            }
        } else {
            result += std::get<1>(tree.find('\0'));
            int symbolCode = static_cast<int>(symbol);
            std::string binSymbolCode = "00000000";
            for (int i = 7; i >= 0; i--) {
                if (symbolCode % 2) {
                    binSymbolCode[i] = '1';
                }
                symbolCode /= 2;
            }
            result += binSymbolCode;
            auto cur = tree.insert(symbol);
            if (isDebug) {
                std::cout << "\'" << symbol << "\' is not in the tree. Adding...\n\n";
                tree.root->colorPrint({cur}, 0);
                std::cout << "\n\'" << symbol << "\' -> " << std::get<1>(tree.find('\0')) + binSymbolCode << '\n';
            }
        }
        auto normalized = tree.normalize();
        if (isDebug) {
            num++;
            std::cout << "Normalizing...\n\n";
            tree.root->colorPrint(normalized, 0);
            std::string enter;
            std::getline(std::cin, enter);
            if (num < str.size())
                std::cout << "\t ||\n\t\\  /\n\t \\/\n\n";
        }
    }
    return result;
}

std::string Tree::decode (std::string &code, bool isDebug) {
    Tree tree;
    std::string result = "", str = code;
    if (isDebug) {
        std::cout << "Decoding...\n\n" << tree << '\n';
    }
    while (code.length() > 0) {
        auto searchResult = tree.find(code);
        if (std::get<0>(searchResult)) {
            if (isDebug) {
                std::cout << str.substr(0, str.length() - code.length()) << " -> " << std::get<1>(searchResult) << '\n';
                str.erase(0, str.length() - code.length());
            }
            result += std::get<1>(searchResult);
            if (std::get<char>(std::get<0>(searchResult)->data) == '\0') {
                auto cur = tree.insert(std::get<1>(searchResult));
                if (isDebug) {
                    std::cout << '\'' << std::get<1>(searchResult) << "\' is not in the tree. Adding...\n\n";
                    tree.root->colorPrint({cur}, 0);
                    std::cout << '\n';
                }
            } else {
                std::get<0>(searchResult)->add();
                if (isDebug) {
                    std::cout << '\'' << std::get<1>(searchResult) << "\' is in the tree. Increasing...\n\n";
                    tree.root->colorPrint({std::get<0>(searchResult)}, 0);
                    std::cout << '\n';
                }
            }
            auto normalized = tree.normalize();
            if (isDebug) {
                std::cout << "Normalizing...\n\n"; 
                tree.root->colorPrint(normalized, 0);
                std::string enter;
                std::getline(std::cin, enter);
                if (code.length())
                    std::cout << "\t ||\n\t\\  /\n\t \\/\n\n";
            }
        } else {
            return "";
        }
    }
    return result;
}

std::pair<std::shared_ptr<Node>, std::string> Tree::recursionFind (std::shared_ptr<Node> node, char data, std::string res) {
    if (std::holds_alternative<char>(node->data)) {
        if (std::get<char>(node->data) == data)
            return std::pair<std::shared_ptr<Node>, std::string>(node, res);
    } else {
        std::pair<std::shared_ptr<Node>, std::string> result {nullptr, ""};
        if (node->left) {
            result = recursionFind(node->left, data, res + "0");
            if (std::get<0>(result))
                return result;    
        }
        if (node->right) {
            result = recursionFind(node->right, data, res + "1");
            if (std::get<0>(result))
                return result;  
        }
    }
    return std::pair<std::shared_ptr<Node>, std::string>(nullptr, "");
}

std::pair<std::shared_ptr<Node>, char> Tree::recursionFind (std::shared_ptr<Node> node, std::string &str) {
    if (!node) {
        std::cerr << "Error: Wrong input string\n";
        return std::pair<std::shared_ptr<Node>, char>(nullptr, '\0');
    }
    if (std::holds_alternative<char>(node->data)) {
        if (std::get<char>(node->data) == '\0') {
            std::string asciiCode = str.substr(0, 8);
            str.erase(0, 8);
            if (asciiCode.length() != 8) {
                std::cerr << "Error: Wrong input string\n";
                return std::pair<std::shared_ptr<Node>, char>(nullptr, '\0');
            }
            char symbol = 0;
            for (int i = 0; i < 8; i++)
                if (asciiCode[i] == '1')
                    symbol += pow(2, 7 - i);
            return std::pair<std::shared_ptr<Node>, char>(node, symbol);
        } else {
            return std::pair<std::shared_ptr<Node>, char>(node, std::get<char>(node->data));
        }
    } else {
        if (str.length() == 0) {
            std::cerr << "Error: Wrong input string\n";
            return std::pair<std::shared_ptr<Node>, char>(nullptr, '\0');
        }
        if (str[0] == '0') {
            str.erase(0, 1);
            return recursionFind(node->left, str);
        } else if (str[0] == '1') {
            str.erase(0, 1);
            return recursionFind(node->right, str);
        } else {
            std::cerr << "Error: Wrong input string\n";
            return std::pair<std::shared_ptr<Node>, char>(nullptr, '\0');
        }
    }
}

std::vector<std::shared_ptr<Node>> Tree::normalize () {
    bool isNorm = true;
    unsigned int curWeight = 0;
    std::vector<std::shared_ptr<Node>>::reverse_iterator iter;
    for (iter = nodeArray.rbegin(); iter != nodeArray.rend(); iter++) {
        if ((*iter)->weight > curWeight)
            curWeight = (*iter)->weight;
        if ((*iter)->weight < curWeight) {
            isNorm = false;
            break;
        }
    }

    std::vector<std::shared_ptr<Node>> used;
    if (!isNorm) {
        std::shared_ptr<Node> temp;
        int pos;
        for (int i = nodeArray.size() - 1; i >= 0; i--)
            if (nodeArray[i]->weight == curWeight) {
                temp = nodeArray[i];
                pos = i;
                break;
            }
        for (int i = 0; i < nodeArray.size(); i++) {
            if (nodeArray[i]->weight < curWeight) {
                std::shared_ptr<Node> cur = nodeArray[i];
                if (cur->parent.lock()->left == cur)
                    cur->parent.lock()->left = temp;
                else
                    cur->parent.lock()->right = temp;
                if (temp->parent.lock()->left == temp)
                    temp->parent.lock()->left = cur;
                else
                    temp->parent.lock()->right = cur;
                std::swap(temp->parent, cur->parent);
                cur->recalculate();
                temp->recalculate();
                nodeArray[i] = temp;
                nodeArray[pos] = cur;
                used.push_back(cur);
                used.push_back(temp);
                break;
            }
        }
        auto elseUsed = this->normalize();
        std::vector<std::shared_ptr<Node>>::iterator it;
        for (it = elseUsed.begin(); it != elseUsed.end(); it++) 
            used.push_back(*it);
    }
    return used;
}
