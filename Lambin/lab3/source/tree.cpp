#include "tree.h"

Tree::Tree (std::string &formula) {
    formula.erase(formula.size() - 1, 1);
    formula.erase(0, 1);
    this->root = createNode(formula);
}

std::ostream &operator<< (std::ostream &out, const Tree &cur) {
    out << cur.root;
    return out;
}

void Tree::transform () {
    transformNode(this->root);
}

bool Tree::checkString (std::string str) {
    if (str[0] != '(' || str[str.size() - 1] != ')')
        return false;
    return Tree::recursionCheck(str);
}

bool Tree::recursionCheck (std::string str) {
    if (str.size() < 5)
        return false;

    int pos1, pos2;
    if (str[1] == '(') {
        pos1 = 1, pos2;
        int counter = 0;
        for (pos2 = pos1; pos2 < str.size(); pos2++) {
            if (str[pos2] == '(')
                counter++;
            if (str[pos2] == ')')
                counter--;
            if (counter == 0)
                break;
        }
        if (recursionCheck(str.substr(pos1, pos2)))
            str.erase(pos1, pos2);
        else 
            return false;
    } else {
        if ((str[1] <= '9' && str[1] >= '0') || (str[1] <= 'Z' && str[1] >= 'A') || (str[1] <= 'z' && str[1] >= 'a')) 
            str.erase(1, 1);
        else
            return false;
    }

    if (str[1] == '+' || str[1] == '-' || str[1] == '*')
        str.erase(1, 1);
    else
        return false;

    if (str[1] == '(') {
        pos1 = 1, pos2;
        int counter = 0;
        for (pos2 = pos1; pos2 < str.size(); pos2++) {
            if (str[pos2] == '(')
                counter++;
            if (str[pos2] == ')')
                counter--;
            if (counter == 0)
                break;
        }
        if (recursionCheck(str.substr(pos1, pos2)))
            str.erase(pos1, pos2);
        else 
            return false;
    } else {
        if ((str[1] <= '9' && str[1] >= '0') || (str[1] <= 'Z' && str[1] >= 'A') || (str[1] <= 'z' && str[1] >= 'a')) 
            str.erase(1, 1);
        else
            return false;
    }
 
    if (str == "()")
        return true;
    else 
        return false;

}

std::shared_ptr<Node> Tree::createNode (std::string expr) {
    if (expr.size() == 1) {
        std::shared_ptr<Node> node(new Node(nullptr, nullptr, expr[0]));
        return node;
    }

    std::string left, right;
    char sign;
    int pos = 0;
    if (expr[0] == '(') {
        int count = 0;
        for (pos; pos < expr.size(); pos++) {
            if (expr[pos] == '(')
                count++;
            if (expr[pos] == ')')
                count--;
            if (count == 0)
                break;
        }
        left = expr.substr(1, pos);
    } else {
        left = expr.substr(0, 1);
    }
    sign = expr[++pos];
    if (expr[pos + 1] == '(') {
        right = expr.substr(pos + 2, expr.size() - pos - 3);
    } else {
        right = expr.substr(pos + 1, 1);
    }
    std::shared_ptr<Node> node(new Node(createNode(left), createNode(right), sign));
    return node;
}

void Tree::transformNode (std::shared_ptr<Node> cur) {
    if (cur->left)
        transformNode(cur->left);
    if (cur->right)
        transformNode(cur->right);

    if (cur->data == '+' && cur->left->data == '*' && cur->right->data == '*') {
        if (cmp(cur->left->left, cur->right->left)) {
            cur->right->left = cur->left->right;
            std::shared_ptr<Node> temp = cur->left->left;
            cur->left->left = nullptr;
            cur->left->right = nullptr;
            cur->left = temp;
            cur->data = '*';
            cur->right->data = '+';
        } else if (cmp(cur->right->right, cur->left->right)) {
            cur->left->right = cur->right->left;
            std::shared_ptr<Node> temp = cur->right->right;
            cur->right->left = nullptr;
            cur->right->right = nullptr;
            cur->right = temp;
            cur->data = '*';
            cur->left->data = '+';
        }
    }
}

bool Tree::cmp (std::shared_ptr<Node> node1, std::shared_ptr<Node> node2) {
    if (node1->data != node2->data)
        return false;

    bool flag = true;
    if (node1->left && node2->left)
        flag = flag && cmp(node1->left, node2->left);
    if ((!node1->left && node2->left) || (node1->left && !node2->left))
        return false;
    if (node1->right && node2->right)
        flag = flag && cmp(node1->right, node2->right);
    if ((!node1->right && node2->right) || (node1->right && !node2->right))
        return false;

    return flag;
}
