#include "H_List.h"

void H_List::set_element(char elem){
    this->elem = elem;
    this->is_elem = false;
    this->number_elem = 0;
}
char H_List::get_is_elem(){
    return this->is_elem;
}
int H_List::get_number_elem(){
    return this->number_elem;
}
Node* H_List::read_node(std::string& list, int& i){
    Node* tmp = new Node;
    if(list[i] == ')'){
        delete tmp;
        return nullptr;
    } 
    else{
        if(list[i] == '('){
            i++;
            tmp->value = read_node(list, i);
            if(std::get<Node*>(tmp->value) == nullptr){
            return tmp;
            }
            i++;
            Node* tmp1 = std::get<Node*>(tmp->value);
            while (list[i] != ')'){
                if( list[i] != ' ') {
                    tmp1->next = read_node(list, i);
                    tmp1->next->next = nullptr;
                    tmp1 = tmp1->next;
                }
                i++;
            }
            return tmp;
        }
        else{
            tmp->value = list[i];
            //tmp->next = nullptr;
        }
    }
    return tmp;
}

void H_List::read_h_list(std::string& list, int& i){
    if(list[i] != ' ' && list[i] != ')'){
        if(list[i] == '(')
            i++;
        this->head = read_node(list, i);
        Node* tmp = this->head;
        i++;
        while (list[i] != ')'){
            if( list[i] != ' ') {
                tmp->next = read_node(list, i);
                tmp->next->next = nullptr;
                tmp = tmp->next;    
            }
            i++;
        }
    }
}

void H_List::print(Node* cur) {
    if (std::holds_alternative<Node *>(cur->value)) {
        std::cout << '(';
        if (std::get<Node*>(cur->value) != nullptr) {
            print(std::get<Node*>(cur->value));
        }
        std::cout << ')';
    }
    else{
        std::cout << std::get<char>(cur->value);
    }
    if (cur->next != nullptr) {
        print(cur->next);
    }
}

void H_List::browse(Node* cur){
    if (std::holds_alternative<Node *>(cur->value)) {
        if (std::get<Node*>(cur->value) != nullptr) {
            browse(std::get<Node*>(cur->value));
        }
    }
    else{
        if(std::get<char>(cur->value) == this->elem){
            this->is_elem = true;
            this->number_elem++;
        }
    }
    if (cur->next != nullptr) {
        browse(cur->next);
    }
}

void H_List::free_list(Node* cur){
    if (std::holds_alternative<Node *>(cur->value)) {
        if (std::get<Node*>(cur->value) != nullptr) {
            free_list(std::get<Node*>(cur->value));
        }
    }
    if (cur->next != nullptr) {
        free_list(cur->next);       
    }
    delete cur;
    
}