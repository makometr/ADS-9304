#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <iomanip>


struct Elem_Pair{
    int key_elem, prior_elem;
};


class bin_tree_node{
public:
    std::shared_ptr<bin_tree_node> left;
    std::shared_ptr<bin_tree_node> right;
    int key, prior;
    bin_tree_node(){};
    bin_tree_node(int key, int prior) : key(key), prior(prior), left(NULL), right(NULL){};
};



Elem_Pair *Elem_Generator(int count){
    srand(time(0));
    Elem_Pair *Elem_Array = new Elem_Pair[count];
    for (int i = 0; i < count; i++){
        Elem_Array[i].key_elem = rand() % 101;
        Elem_Array[i].prior_elem = rand() % 101;
    }
    return Elem_Array;
}




void split(std::shared_ptr<bin_tree_node> t, int key, std::shared_ptr<bin_tree_node> &left, std::shared_ptr<bin_tree_node> &right){
    if (!t){
        left = right = NULL;
    } else if (key < t -> key){
        split(t -> left, key, left, t -> left);
        right = t;
    } else {
        split(t -> right, key, t -> right, right);
        left = t;
    }
}



void insert (std::shared_ptr<bin_tree_node> &t, std::shared_ptr<bin_tree_node> it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it -> key, it -> left, it -> right),  t = it;
    else if (it -> key < t -> key){
        insert(t -> left, it);
    } else {
        insert(t->right, it);
    }
}


std::shared_ptr<bin_tree_node> Treaps_Generator(int count){
    if (count < 0){
        std::cout << "there must be at least 1 element\n";
        return nullptr;
    }

    Elem_Pair *seq = Elem_Generator(count);
    for(int i = 0; i < count; i++){
        std::cout << seq[i].key_elem << " " << seq[i].prior_elem << "\n";
    }
    std::shared_ptr<bin_tree_node> Array_Items[count];
    for (int i = 0; i < count; i++){
        Array_Items[i] = std::make_shared<bin_tree_node>();
        Array_Items[i] -> key = seq[i].key_elem;
        Array_Items[i] -> prior = seq[i].prior_elem;
    }
    for (int i = 1; i < count; i++){
        insert(Array_Items[0], Array_Items[i]);
    }
    delete []seq;
    return Array_Items[0];
}



std::shared_ptr<bin_tree_node> Treaps_Building(Elem_Pair *seq, std::vector<int> vec){
    std::shared_ptr<bin_tree_node> Array_Items[vec.size() / 2];
    for (int i = 0; i < vec.size() / 2; i++){
        Array_Items[i] = std::make_shared<bin_tree_node>();
        Array_Items[i] -> key = seq[i].key_elem;
        Array_Items[i] -> prior = seq[i].prior_elem;
    }
    for (int i = 1; i < vec.size() / 2; i++){
        insert(Array_Items[0], Array_Items[i]);
    }
    return Array_Items[0];
}


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
    if (t -> key == key && t -> prior == prior){
        Merge(t, t -> left, t -> right);
    } else {
        if (key < t -> key){
            Erase(t -> left, key, prior);
        } else {
            Erase(t -> right, key, prior);
        }
    }
}

bool string_checker(std::string &str, int &index, std::vector<int> &vec){
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
        return string_checker(str, index, vec);
    } else {
        return true;
    }
}





void display_Treap(std::shared_ptr<bin_tree_node> root, int space = 0, int height = 10) { //display treap
    if (root == nullptr)
        return;
    space += height;
    display_Treap(root->right, space);
    std::cout << '\n';
    for (int i = height; i < space; i++)
        std::cout << ' ';
    std::cout << root -> key << "(" << root -> prior << ")\n";
    std::cout << '\n';
    display_Treap(root->left, space);
}








int main(int argc, char* argv[]) {
    std::shared_ptr<bin_tree_node> head = std::make_shared<bin_tree_node>();
    if(argc == 1){
        std::cout << "Wrong expression\n";
        return 0;
    }
    std::string str(argv[1]);
    int index = 0;
    std::vector<int> vec;
    bool k = string_checker(str, index, vec);
    Elem_Pair seq[vec.size() / 2];
    if (k){
        for (int i = 0; vec[i]; i += 2){
            seq[i / 2].key_elem = vec[i];
            seq[i / 2].prior_elem = vec[i + 1];
        }
        std::cout << "success\n";
        head = Treaps_Building(seq, vec);
        display_Treap(head);

    } else {
        std::cout << "wrong string\n";
        return 0;
    }
    return 0;
}