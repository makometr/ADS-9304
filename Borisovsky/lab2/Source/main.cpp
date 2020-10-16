#include <iostream>
#include <variant>



struct Node{
    Node* next;
    std::variant<Node*, std::string> val;
};

void deleter(Node *head);



bool create_list(Node **head, std::string &str, int &index){
    bool check = true;
    if (str[index] != '('){
        return false;
    }

    index++;

    while(str[index] != ')' && index < str.length()){
        if (isalpha(str[index]) && (str[index - 1] == '(' || str[index - 1] == ' ')){
            std::string elem = "";
            elem += str[index];
            if (!*head){
                *head = new Node;
                Node *ptr = *head;
                ptr -> val = elem;
                ptr -> next = nullptr;
                index++;
            } else {
                Node *ptr = *head;
                while (ptr -> next){
                    ptr = ptr -> next;
                }
                ptr -> next = new Node;
                ptr -> next -> val = elem;
                ptr -> next -> next = nullptr;
                index++;
            }
        }

        else if (str[index] == ' ' && (isalpha(str[index - 1]) || str[index - 1] == ')')){
            index++;
        }

        else if(str[index] == '(' && (str[index - 1] == ' ' || str[index - 1] == '(')){
            if (!*head){
                *head = new Node;
                Node *ptr = *head;
                ptr -> val = nullptr;
                ptr -> next = nullptr;
                check = create_list(&std::get<Node*>(ptr -> val), str, index);
                if (!check){
                    return false;
                }
                index++;
            } else {
                Node *ptr = *head;
                while (ptr -> next){
                    ptr = ptr -> next;
                }
                ptr -> next = new Node;
                ptr -> next -> val = nullptr;
                ptr -> next -> next = nullptr;
                check = create_list(&std::get<Node*>(ptr -> next -> val), str, index);
                if (!check){
                    return false;
                }
                index++;
            }
        }

        else{
            index = str.length();
            return false;
        }
    }
    if (index == str.length()){
        return false;
    } else {
        return true;
    }

}

int levels_counter(Node* head, int &counter){
    Node* ptr = head;
    int flag = 1;
    while (ptr){
        if (std::holds_alternative<Node*>(ptr -> val)){
            if (flag){
                counter++;
            }
            flag = 0;
            if(std::get<Node*>(ptr -> val)){
                levels_counter(std::get<Node*>(ptr -> val), counter);
            }
        }
        ptr = ptr -> next;
    }
    return counter;
}

void deleter(Node *head){
    if (head -> next){
        deleter (head -> next);
    }
    if (std::holds_alternative<Node*>(head -> val)){
        if (std::get<Node*>(head -> val)){
            deleter(std::get<Node*>(head -> val));
        }
    }
    delete head;
}


int main(int argc, char* argv[]) {
    if(argc == 1){
        std::cout << "Wrong expression\n";
        return 0;
    }

    int index = 0;
    int counter = 0;
    std::string str(argv[1]);
    Node *head = nullptr;
    bool checker = true;
    checker = create_list(&head, str, index);
    if (checker){
        std::cout << "This list have: " << levels_counter(head, counter) << " level\n";
    } else {
        std::cout << "Wrong expression\n";
    }

    if(head){
        deleter(head);
    }

    return 0;
}
