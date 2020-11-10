/*11у вариант: Преобразовать ЛКП перечисление в КЛП и ЛПК БД, и если все некорневые ноды - числа,
 * вычислить интовое значение (указатели).
*/

#include <iostream>
#include <memory>
#include <string>

template <typename T>
struct Node{
    std::shared_ptr<Node<T>> left, right;
    T data;
};

template <typename T>
class Tree {

private:
    std::shared_ptr<Node<T>> construct(std::string& str)
    {
        if(str.length() < 3) {
            return nullptr;
        } else if(str.length() == 3) {
            std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();
            node->left = nullptr;
		    node->right = nullptr;
		    node->data = str[1];
            return node;
        } else {
            int iter = 2;
            for(int count = 1; count; iter++) {
                if(str[iter] == '(') {
                    count++;
                } else if(str[iter] == ')') {
                    count--;
                }
            }
            std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>();
            node->data = str[iter];
            std::string left = str.substr(1, iter-1);
            std::string right = str.substr(iter+1,(str.size()-2-iter));
            node->left = construct(left);
            node->right = construct(right);
            return node;
        }
    }

    void print_expression(std::shared_ptr<Node<T>>& node_ptr) {
        std::string math_sym = "*-+";
        std::cout << '(';
        if(node_ptr->left != nullptr) {
            if(math_sym.find_first_of(node_ptr->left->data) == std::string::npos) {
                std::cout << node_ptr->left->data;
            } else {
                print_expression(node_ptr->left);
            }
        } else {
            std::cout << '_';
        }
        std::cout << node_ptr->data;
        if(node_ptr->right != nullptr) {
            if(math_sym.find_first_of(node_ptr->right->data) == std::string::npos) {
                std::cout << node_ptr->right->data;
            } else {
                print_expression(node_ptr->right);
            }
        } else {
            std::cout << '_';
        }
        std::cout << ')';
    }

    void print_expression_KLP(std::shared_ptr<Node<T>>& node_ptr) {
        std::string math_sym = "*-+";
        std::cout << '(';
        std::cout << node_ptr->data;
        if(node_ptr->left != nullptr) {
            if(math_sym.find_first_of(node_ptr->left->data) == std::string::npos) {
                std::cout << node_ptr->left->data;
            } else {
                print_expression_KLP(node_ptr->left);
            }
        } else {
            std::cout << '_';
        }
        if(node_ptr->right != nullptr) {
            if(math_sym.find_first_of(node_ptr->right->data) == std::string::npos) {
                std::cout << node_ptr->right->data;
            } else {
                print_expression_KLP(node_ptr->right);
            }
        } else {
            std::cout << '_';
        }
        std::cout << ')';
    }

    void print_expression_LPK(std::shared_ptr<Node<T>>& node_ptr) {
        std::string math_sym = "*-+";
        std::cout << '(';
        if(node_ptr->left != nullptr) {
            if(math_sym.find_first_of(node_ptr->left->data) == std::string::npos) {
                std::cout << node_ptr->left->data;
            } else {
                print_expression_LPK(node_ptr->left);
            }
        } else {
            std::cout << '_';
        }
        if(node_ptr->right != nullptr) {
            if(math_sym.find_first_of(node_ptr->right->data) == std::string::npos) {
                std::cout << node_ptr->right->data;
            } else {
                print_expression_LPK(node_ptr->right);
            }
        } else {
            std::cout << '_';
        }
        std::cout << node_ptr->data;
        std::cout << ')';
    }

public:
    std::shared_ptr<Node<T>> head;

    Tree<T>(std::string& str) {
        this->head = construct(str);
        if(!isalnum(this->head->data)) {
            print_KLP();
            print_LPK();
            print_LKP();
        } else {
            std::cout << "Expression: (" << this->head->data << ")\n";
        }
        if(!scan_char(this->head)) {
            std::cout << "Expression = " << count_tree(this->head) << '\n';
        }
    }

    void print_KLP() {
        this->print_expression_KLP(this->head);
        std::cout << '\n';
    }

    void print_LPK() {
        this->print_expression_LPK(this->head);
        std::cout << '\n';
    }

    void print_LKP() {
        std::cout << "Expression: ";
        this->print_expression(this->head);
        std::cout << '\n';
    }

    bool scan_char(std::shared_ptr<Node<T>>& node_ptr) {
        if(node_ptr == nullptr) {
            return false;
        }
        return (isalpha(node_ptr->data) || scan_char(node_ptr->left) || scan_char(node_ptr->right));
    }

    int count_tree(std::shared_ptr<Node<T>>& node_ptr) {
        int a,b;
        if(node_ptr->left != nullptr) {
            if(isdigit(node_ptr->left->data)) {
                a = node_ptr->left->data - '0';
            } else {
                a = count_tree(node_ptr->left);
            }
        } else {
            a = 0;
        }
        if(node_ptr->right != nullptr) {
            if(isdigit(node_ptr->right->data)) {
                b = node_ptr->right->data - '0';
            } else {
                b = count_tree(node_ptr->right);
            }
        } else {
            b = 0;
        }
        if(node_ptr->data == '*') {
            return a*b;
        } else if(node_ptr->data == '-') {
            return a-b;
        } else if(node_ptr->data == '+') {
            return a+b;
        } else {
            std::cerr << "Err: unexpected symbol";
            exit(1);
        }
    }

    void insert_node(std::shared_ptr<Node<T>> path, std::string side, T data) {
        std::string math_sym = "*-+";
        bool is_left = !side.compare("left");
        bool is_right = !side.compare("right");
        if(math_sym.find_first_of(path->data) != std::string::npos) {
            if(is_left) {
                path->left = std::make_shared<Node<T>>();
                path->left->left = nullptr;
                path->left->right = nullptr;
                path->left->data = data;
            } else if(is_right) {
                path->right = std::make_shared<Node<T>>();
                path->right->left = nullptr;
                path->right->right = nullptr;
                path->right->data = data;
            } else {
                std::cout << "Wrong side\nNode was not included\n";
            }
        } else {
            std::cout << "Path node is terminal\nNode was not included\n";
        }
    }

    void delete_node(std::shared_ptr<Node<T>> path, std::string side) {
        std::string math_sym = "*-+";
        bool is_left = !side.compare("left");
        bool is_right = !side.compare("right");
        if(is_left) {
            if(math_sym.find_first_of(path->left->data) != std::string::npos) {
                if(path->left->left != nullptr) {
                    delete_node(path->left, "left");
                }
                if(path->left->right != nullptr) {
                    delete_node(path->left, "right");
                }       
            }
            path->left = nullptr;
        } else if (is_right) {
            if(math_sym.find_first_of(path->right->data) != std::string::npos) {
                if(path->right->left != nullptr) {
                    delete_node(path->right, "left");
                }
                if(path->right->right != nullptr) {
                    delete_node(path->right, "right");
                }       
            }
            path->right = nullptr;
        } else {
            std::cout << "Wrong side\nNode was not deleted\n";
        }
    }

/*
1 * 2
()
(a)
((a)*(b))
(((a)+(b))*((c)-(d)))
(((6)*(7))-((8)+(9)))
Инфикс: a+b*c-d
Префикс: *+ab-cd
Постфикс: ab+cd-*
*/
};

bool checktreestring(std::string& str) {
    std::string math_sym = "*-+";
    for(int i = 0; i< str.length()-1; i++) {
        if(math_sym.find_first_of(str[i]) != std::string::npos && (str[i-1] != ')' || str[i+1] != '(')) {
            return false;
        } else if(isalnum(str[i]) && (str[i-1] != '(' || str[i+1] != ')')) {
            return false;
        } else if(str[i] == ')' && str[i+1] == '(') {
            return false;
        }
    }
    return true;
}

bool checkstring(std::string& str) {
    std::string good_char = "*-+()";
    std::string new_str;
    int count = 0;
    for(auto iter = str.begin();iter != str.end(); iter++) {
        if(isspace(*iter)) {
            continue;
        } else if(*iter == '(') {
            count++;
        } else if(*iter == ')') {
            count--;
            if(count<0){
                return false;
            }
        } else if(!isalnum(*iter) && good_char.find_first_of(*iter) == std::string::npos) {
            return false;
        }
        new_str.push_back(*iter);
    }
    if(count) {
        return false;
    }
    str = new_str;
    if(str[0] != '(' || str[str.length()-1] != ')') {
        return false;
    }
    return checktreestring(str);
}

int main() {
    std::string str;
    std::cin.ignore (std::string::npos,'\n');
    std::getline(std::cin,str);
    if(!checkstring(str)) {
        std::cout << "Incorrect string!\n";
        return 0;
    }
    //str = "(((a)*(b))+((c)*()))";
    Tree<char> tree(str);
    //tree.insert_node(tree.head->right, "right", '6');
    //tree.print_LKP();
    return 0;
}
