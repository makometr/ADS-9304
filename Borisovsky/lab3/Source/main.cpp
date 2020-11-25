#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <cstdlib>

//проверка на работу с char
bool char_checker(std::string &str){
    if (str[str.length() - 1] == 'c'){
        return true;
    } else {
        return false;
    }
}

//проверка на работу с int
bool int_checker(std::string &str){
    if (str[str.length() - 1] == 'i'){
        return true;
    } else {
        return false;
    }
}

//валидация строка до последней закрывающей скобки
bool first_checker(std::string &str, int &index){
    if (str[index] != '('){
        return false;
    }
    index++;
    if (char_checker(str)) {
        if (str[index] != '(' && str[index] != ')') {
            index++;
        } else if (str[index] == ')') {
            return true;
        } else if (str[index] == '(') {
            return false;
        }
        if (str[index] == ')') {
            return true;
        }
    } else if (int_checker(str)){
        if (str[index] != '(' && str[index] != ')') {
            std::string check_num = "";
            while (str[index] != '(' && str[index] != ')') {
                check_num += str[index];
                index++;
            }
            if (!check_num.empty()) {
                char *endptr;
                const char *c_string = check_num.c_str();
                strtol(c_string, &endptr, 10);
                if (*endptr) {
                    return false;
                }
            } else {
                return false;
            }
        } else if (str[index] == ')') {
            return true;
        } else if (str[index] == '(') {
            return false;
        }
        if (str[index] == ')') {
            return true;
        }
    }

    if (!first_checker(str, index)){
        return false;
    }
    index++;
    if (!first_checker(str, index)){
        return false;
    }
    index++;

    if (str[index] == ')'){
        return true;
    } else {
        return false;
    }
}


//проверка на то, что строка кончается валидно
bool second_checker(std::string &str){
    int index = 0;
    if(first_checker(str, index) && index + 2 == str.length()){
        return true;
    } else {
        return false;
    }
}


//структура узла бинарного дерева
template <typename T>
class bin_tree_node{
public:
    std::shared_ptr<bin_tree_node<T>> left;
    std::shared_ptr<bin_tree_node<T>> right;
    T data;
};


//бинарное дерево
template<typename T>
class bin_tree{
public:
    std::shared_ptr<bin_tree_node<T>> head;
    //реализация конструктора (валидация строки)
    bin_tree(std::string &str){
        int index = 0;
        bool check = second_checker(str);
        if (check){
            head = create_bin_tree(str, index);
        } else {
            std::cout << "wrong string\n";
            head = nullptr;
        }
    }
    ~bin_tree() = default;

    //создание бинарного дерева
    std::shared_ptr<bin_tree_node<T>> create_bin_tree(std::string &str, int &index){
        std::shared_ptr<bin_tree_node<T>> node = std::make_shared<bin_tree_node<T>>();
        index++;
        if (str[index] == ')'){
            index++;
            return nullptr;
        } else {
            if (int_checker(str)) {
                std::string check_num = "";
                while (str[index] != '(' && str[index] != ')') {
                    check_num += str[index];
                    index++;
                }
                node->data = strtol(check_num.c_str(), NULL, 10);
            } else if (char_checker(str)){
                node -> data = str[index];
                index++;
            }
        }


        if (str[index] == ')'){
            node -> left = nullptr;
            node -> right = nullptr;
            index++;
            return node;
        } else {
            node -> left = create_bin_tree(str, index);
            node -> right = create_bin_tree(str, index);
            index ++;
            return node;
        }
    }


    //выполнения задания лабороторной (посредством обхода в ширину)
    void show_tree(){
        std::cout << "success: ";
        std::queue<std::shared_ptr<bin_tree_node<T>>> queue;
        queue.push(head);
        while (!queue.empty()) {
            std::shared_ptr<bin_tree_node<T>> tmp = queue.front();
            queue.pop();
            std::cout << tmp->data << " ";
            if (tmp -> left) {
                queue.push(tmp->left);
            }

            if (tmp -> right) {
                queue.push(tmp->right);
            }

        }
    }


    //LKP обход
    void LKP(std::shared_ptr<bin_tree_node<T>> hd){
        if (hd -> left){
            LKP(hd -> left);
        }
        std::cout << hd -> data << " ";
        if (hd -> right){
            LKP(hd -> right);
        }
    }

    //вставка элемента
    void insert_elem(std::shared_ptr<bin_tree_node<T>> hd, T elem){
        while(hd->left) {
            hd = hd->left;
        }
        hd->left = std::make_shared<bin_tree_node<T>>();
        hd->left->left = nullptr;
        hd->left->right = nullptr;
        hd->left->data = elem;
    }

    //удаление элемента
    void delete_elem(std::shared_ptr<bin_tree_node<T>> hd, T elem){
        if(hd->left != nullptr && hd->left -> data == elem){
            hd->left = nullptr;
        }
        if(hd -> right != nullptr && hd -> right -> data == elem){
            hd -> right = nullptr;
        }

        if(hd -> left != nullptr)
            delete_elem(hd -> left, elem);
        if(hd -> right != nullptr)
            delete_elem(hd -> right, elem);
    }

};




int main(int argc, char* argv[]){
    if(argc == 1){
        std::cout << "Wrong expression\n";
        return 0;
    }
    std::string str(argv[1]);
    if (char_checker(str)){
        bin_tree<char> bt(str);
        if (bt.head){
            bt.show_tree();
        }
    } else if (int_checker(str)){
        bin_tree<int> bt(str);
        if (bt.head){
            bt.show_tree();
        }
    } else {
        std::cout << "wrong string\n";
    }
}