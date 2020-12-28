#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <fstream>



static int oper_counter = 0;

// структура элемента дерева
struct Elem_Pair{
    int key_elem, prior_elem;
};


// класс узла дерева
class bin_tree_node{
public:
    std::shared_ptr<bin_tree_node> left;
    std::shared_ptr<bin_tree_node> right;
    int key, prior;
    bin_tree_node(){};
    bin_tree_node(int key, int prior) : key(key), prior(prior), left(NULL), right(NULL){};
};



// генератор рандомных элементов
Elem_Pair *Elem_Generator(int count){
    Elem_Pair *Elem_Array = new Elem_Pair[count];
    for (int i = 0; i < count; i++){
        Elem_Array[i].key_elem = rand() % 1001;
        Elem_Array[i].prior_elem = rand() % 1001;
    }
    return Elem_Array;
}


// генератор возрастающих элементов
Elem_Pair *Increasing_Elem_Generator(int count){
    Elem_Pair *Elem_Array = new Elem_Pair[count];
    for (int i = 0; i < count; i++){
        Elem_Array[i].key_elem = i;
        Elem_Array[i].prior_elem = i;
    }
    return Elem_Array;
}



// функция разделения дерева в два поддерева
void Split(std::shared_ptr<bin_tree_node> t, int key, std::shared_ptr<bin_tree_node> &left, std::shared_ptr<bin_tree_node> &right){
    //oper_counter++;
    if (!t){
        left = right = NULL;
    } else if (key < t -> key){
        Split(t->left, key, left, t->left);
        right = t;
    } else {
        Split(t->right, key, t->right, right);
        left = t;
    }
}



// функция вставки элемента в дерево
void Insert (std::shared_ptr<bin_tree_node> &t, std::shared_ptr<bin_tree_node> it) {
    oper_counter++;
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        Split(t, it->key, it->left, it->right), t = it;
    else if (it -> key < t -> key){
        Insert(t->left, it);
    } else {
        Insert(t->right, it);
    }
}


// генератор рандомной дерамиды
std::shared_ptr<bin_tree_node> Treaps_Generator(int count){
    if (count < 0){
        std::cout << "there must be at least 1 element\n";
        return nullptr;
    }

    Elem_Pair *seq = Elem_Generator(count);
    std::shared_ptr<bin_tree_node> *Array_Items = new std::shared_ptr<bin_tree_node>[count];
    for (int i = 0; i < count; i++){
        Array_Items[i] = std::make_shared<bin_tree_node>();
        Array_Items[i] -> key = seq[i].key_elem;
        Array_Items[i] -> prior = seq[i].prior_elem;
    }
    for (int i = 1; i < count; i++){
        Insert(Array_Items[0], Array_Items[i]);
    }
    delete []seq;
    std::shared_ptr<bin_tree_node> head = std::make_shared<bin_tree_node>();
    head = Array_Items[0];
    delete []Array_Items;
    return head;
}

// генератор дерамиды с возрастающими элементами
std::shared_ptr<bin_tree_node> Increasing_Treaps_Generator(int count){
    if (count < 0){
        std::cout << "there must be at least 1 element\n";
        return nullptr;
    }

    Elem_Pair *seq = Increasing_Elem_Generator(count);
    std::shared_ptr<bin_tree_node> *Array_Items = new std::shared_ptr<bin_tree_node>[count];
    for (int i = 0; i < count; i++){
        Array_Items[i] = std::make_shared<bin_tree_node>();
        Array_Items[i] -> key = seq[i].key_elem;
        Array_Items[i] -> prior = seq[i].prior_elem;
    }
    for (int i = 1; i < count; i++){
        Insert(Array_Items[0], Array_Items[i]);
    }
    delete []seq;
    std::shared_ptr<bin_tree_node> head = std::make_shared<bin_tree_node>();
    head = Array_Items[0];
    delete []Array_Items;
    return head;
}


// создание дерамиды по переданным значениям
std::shared_ptr<bin_tree_node> Treaps_Building(Elem_Pair *seq, std::vector<int> vec){
    std::shared_ptr<bin_tree_node> Array_Items[vec.size() / 2];
    for (int i = 0; i < vec.size() / 2; i++){
        Array_Items[i] = std::make_shared<bin_tree_node>();
        Array_Items[i] -> key = seq[i].key_elem;
        Array_Items[i] -> prior = seq[i].prior_elem;
    }
    for (int i = 1; i < vec.size() / 2; i++){
        Insert(Array_Items[0], Array_Items[i]);
    }
    return Array_Items[0];
}


// функция объединения двух поддеревьев
void Merge(std::shared_ptr<bin_tree_node> &t, std::shared_ptr<bin_tree_node> left, std::shared_ptr<bin_tree_node> right){
    if (!left || !right){
        t = left ? left : right;
    } else if (left -> prior > right -> prior){
        Merge(left -> right, left -> right, right);
        t = left;
    } else {
        Merge(right -> left, left, right -> left);
        t = right;
    }
}

void Erase(std::shared_ptr<bin_tree_node> &t, int key, int prior){
    oper_counter++;
    if (!t || t -> prior < prior){
        std::cout << "Element with stack parameters not found\n";
        return;
    }
    if (t -> key == key && t -> prior == prior){
        Merge(t, t -> left, t -> right);
        return;
    } else {
        if (key < t -> key){
            Erase(t -> left, key, prior);
        } else {
            Erase(t -> right, key, prior);
        }
    }
}


// проверка строки на валидность
bool String_Checker(std::string &str, int &index, std::vector<int> &vec){
    if (str[index] != '('){
        return false;
    }
    index++;
    std::string check_num = "";
    while (str[index] != ' ' && str[index]){
        check_num += str[index];
        index++;
    }
    if (!str[index]){
        return false;
    }
    if (!check_num.empty()) {
        char *endptr;
        const char *c_string = check_num.c_str();
        vec.push_back(strtol(c_string, &endptr, 10));
        if (*endptr) {
            return false;
        }
    } else {
        return false;
    }
    index++;
    check_num = "";
    while (str[index] != ')' && str[index]){
        check_num += str[index];
        index++;
    }
    if (!str[index]){
        return false;
    }
    if (!check_num.empty()) {
        char *endptr;
        const char *c_string = check_num.c_str();
        vec.push_back(strtol(c_string, &endptr, 10));
        if (*endptr) {
            return false;
        }
    } else {
        return false;
    }
    if (str[index + 1]){
        index++;
        return String_Checker(str, index, vec);
    } else {
        return true;
    }
}




// печать дерева на экран
void Display_Treap(std::shared_ptr<bin_tree_node> root, int space = 0, int height = 5) { //display treap
    if (root == nullptr)
        return;
    space += height;
    Display_Treap(root->right, space);
    std::cout << '\n';
    for (int i = height; i  < space; i++)
        std::cout << ' ';
    std::cout << root -> key << "(" << root -> prior << ")\n";
    Display_Treap(root->left, space);
}






class Analysis{
    std::ofstream insert_middle_case;
    std::ofstream insert_worst_case;
    std::ofstream erase_middle_case;
    std::ofstream erase_worst_case;
public:
    void start_insert_middle(){
        std::shared_ptr<bin_tree_node> head;
        std::shared_ptr<bin_tree_node> insert_elem;
        insert_elem = std::make_shared<bin_tree_node>();
        insert_elem = Treaps_Generator(1);
        insert_middle_case.open("insert_middle_case.txt");
        for (int i = 1; i < 1000000; i += 10000){
            insert_middle_case << i;
            head = Treaps_Generator(i);
            oper_counter = 0;
            double value_oper = 0;
            for (int j = 0; j < 50; j++){
                Insert(head, insert_elem);
                value_oper += oper_counter;
                insert_elem = Treaps_Generator(1);
                value_oper = 0;
            }
            insert_middle_case << " " << oper_counter / 50 << '\n';
        }
        insert_middle_case.close();
    };
    void start_insert_worst(){
        std::shared_ptr<bin_tree_node> head;
        std::shared_ptr<bin_tree_node> insert_elem;
        insert_elem = std::make_shared<bin_tree_node>();
        insert_elem = Treaps_Generator(1);
        insert_worst_case.open("insert_worst_case.txt");
        for (int i = 1; i < 10000; i += 100){
            insert_worst_case << i;
            head = Increasing_Treaps_Generator(i);
            oper_counter = 0;
            double value_oper = 0;
            for (int j = 0; j < 50; j++){
                Insert(head, insert_elem);
                value_oper += oper_counter;
                insert_elem = Treaps_Generator(1);
                value_oper = 0;
            }
            insert_worst_case << " " << oper_counter / 50 << '\n';
        }
        insert_worst_case.close();
    };
    void start_erase_middle(){
        std::shared_ptr<bin_tree_node> head;
        std::shared_ptr<bin_tree_node> insert_elem;
        insert_elem = std::make_shared<bin_tree_node>();
        insert_elem = Treaps_Generator(1);
        erase_middle_case.open("erase_middle_case.txt");
        for (int i = 1; i < 1000000; i += 10000){
            erase_middle_case << i;
            head = Treaps_Generator(i);
            oper_counter = 0;
            double value_oper = 0;
            for (int j = 0; j < 50; j++){
                Erase(head, insert_elem -> key, insert_elem -> prior);
                value_oper += oper_counter;
                insert_elem = Treaps_Generator(1);
                value_oper = 0;
            }
            erase_middle_case << " " << oper_counter / 50 << '\n';
        }
        erase_middle_case.close();
    };
    void start_erase_worst(){
        std::shared_ptr<bin_tree_node> head;
        std::shared_ptr<bin_tree_node> insert_elem;
        insert_elem = std::make_shared<bin_tree_node>();
        insert_elem = Treaps_Generator(1);
        erase_worst_case.open("erase_worst_case.txt");
        for (int i = 1; i < 10000; i += 100){
            erase_worst_case << i;
            head = Increasing_Treaps_Generator(i);
            oper_counter = 0;
            double value_oper = 0;
            for (int j = 0; j < 50; j++){
                Erase(head, insert_elem -> key, insert_elem -> prior);
                value_oper += oper_counter;
                insert_elem = Treaps_Generator(1);
                value_oper = 0;
            }
            erase_worst_case << " " << oper_counter / 50 << '\n';
        }
        erase_worst_case.close();
    };

};



int main(int argc, char* argv[]) {
    srand(time(0));
    std::shared_ptr<bin_tree_node> head = std::make_shared<bin_tree_node>();
    if(argc == 1){
        std::cout << "Wrong expression\n";
        return 0;
    }
    //Analysis analys;
    //analys.start_erase_worst();
    //return 0;
    char *endptr;
    std::string str(argv[1]);
    char what_to_do_one = argv[2][0];
    int key = strtol(argv[3], &endptr, 10);
    int prior = strtol(argv[4], &endptr, 10);
    char what_to_do_two = argv[5][0];
    int index = 0;
    std::vector<int> vec;
    bool k = String_Checker(str, index, vec);
    Elem_Pair seq[vec.size() / 2];
    if (k){
        for (int i = 0; vec[i]; i += 2){
            seq[i / 2].key_elem = vec[i];
            seq[i / 2].prior_elem = vec[i + 1];
        }
        std::cout << "success\n";
        head = Treaps_Building(seq, vec);
        Display_Treap(head);
        while (true){
            char what_to_do;
            std::cout << "if you want to exit press 'e' and if you want to delete an item press 'd' or Insert item press 'i': ";
            what_to_do  = what_to_do_one;
            if (what_to_do == 'e'){
                return 0;
            } else if (what_to_do == 'd'){
                std::cout << "Enter the key and priority of the item you want to remove: ";
                Erase(head, key, prior);
                std::cout << "\n\n\n";
                Display_Treap(head);
                what_to_do_one = what_to_do_two;
            } else if (what_to_do == 'i'){
                std::cout << "Enter the key and priority of the item you want to Insert: ";
                std::shared_ptr<bin_tree_node> insert_elem = std::make_shared<bin_tree_node>();
                insert_elem -> key = key;
                insert_elem -> prior = prior;
                Insert(head, insert_elem);
                std::cout << "\n\n\n";
                Display_Treap(head);
                what_to_do_one = what_to_do_two;
            } else {
                std::cout << "You entered an invalid character.\n";
                return 0;
            }
        }

    } else {
        std::cout << "wrong string\n";
        return 0;
    }
}