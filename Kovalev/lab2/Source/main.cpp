#include <iostream>
#include <cstdlib>
#include <variant>

struct Node{

    Node* next;
    std::variant<Node*, std::string> data;

};

struct Elem{

    Elem* next;
    std::string data;

};

class linkedList{

    std::string argLine;
    Node* head;
    Elem* uniquePtr;
    int length;
    int error;
    int counter;

public:

    linkedList(std::string& st){

        this->head = nullptr;
        this->uniquePtr = nullptr;
        this->argLine = "";
        this->length = st.length();
        this->counter = 0;

        if(listEndsChecker(st)){
            int iter = 1;
            this->error = 0;
            addNode(&this->head, iter, st, error);
            if(!error) {
                getAtoms(this->head, this->argLine);
                if(this->argLine != "") {
                    counting(this->argLine, this->counter);

                    this->uniquePtr = createLinearList(argLine, this->counter);

                    printer(uniquePtr);

                    listDeleter(this->uniquePtr);

                    deleter(this->head);
            }else{
                    std::cout << "Correct!\n";
                }
            }else{
                std::cout << "Wrong expression!" << '\n';
                if(this->head) {
                    deleter(this->head);
                }
            }
            
        }
    }

    bool listEndsChecker(const std::string& s) const{
        if(s[0] == '(' && s[length - 1] == ')') {
            int br = 0;
            for(int i = 0; i < length; i++){
                if(s[i] == '('){
                    br++;
                }
                if(s[i] == ')'){
                    br--;
                }
            }
            if(!br) {
                return true;
            }else{
                return false;
            }
        }
        else{
            std::cout << "Wrong expression!" << '\n';
            return false;
        }
    }

    void addNode(Node** ptr, int& iter, const std::string& s, int& err) {
        if(iter < this->length) {
            if (s[iter] != ')') {
                if (s[iter] == ' ') {
                    iter = iter + 1;
                }
                if (s[iter] != '(') {
                    if (s[iter] == ' ') {
                        iter = iter + 1;
                    }
                    if (isalpha(s[iter])){

                        std::string el = "";
                        int end = 0;
                        while(isalpha(s[iter + end])){
                            el = el + s[iter + end];
                            end++;
                        }

                        Node *tmp = new Node;
                        tmp->next = nullptr;
                        tmp->data = el;

                        *ptr = tmp;
                        iter = iter + end;
                        addNode(&((*ptr)->next), iter, s, err);

                    }else if (s[iter] == ')'){
                        iter = iter + 1;
                        return;
                    }else{
                        err = 1;
                        return;
                    }
                    iter = iter + 1;
                    addNode(&(*ptr)->next, iter, s, err);
                }else{

                        Node *tmp = new Node;
                        tmp->next = nullptr;
                        tmp->data = nullptr;

                        *ptr = tmp;

                        iter = iter + 1;
                        addNode(&(std::get<Node*>((*ptr)->data)), iter, s, err);
                }
                addNode(&(*ptr)->next, iter, s, err);
            }else{
                iter = iter + 1;
                return;
            }
        }
    }

    void getAtoms(Node* ptr, std::string& argLine){
        Node* tmp = ptr;
        while(tmp){
            if(std::holds_alternative<Node*>(tmp->data)){
                getAtoms(std::get<Node*>(tmp->data), argLine);
            }
            if(std::holds_alternative<std::string>(tmp->data)) {
                argLine = argLine + std::get<std::string>(tmp->data) + ' ';
            }
            tmp = tmp->next;
        }
    }

    void counting(std::string& s, int& num){
        int spaceCounter = 0;
        while(s[s.length() - 1 - spaceCounter] == ' '){
            spaceCounter++;
        }

        for(int i = 0; i < s.length(); i++){
            if(s[i] == ' '){
                num++;
            }
        }
        num = num - spaceCounter;
        num++;
    }

    Elem* createLinearList(std::string& args, int& count){
        std::string el = "";
        int it = 0;
        Elem* head = nullptr;
        Elem* tail = new Elem;

        while(args[it] != ' '){
            el = el + args[it];
            it++;
        }
        it++;
        tail->data = el;
        el.clear();
        tail->next = nullptr;
        head = tail;

        for(int i = 0; i < count - 1; i++){
            while(args[it] != ' '){
                el = el + args[it];
                it++;
            }
            it++;
            tail->next = addLinElem(el);
            el.clear();
            tail = tail->next;
        }

        return head;
    }

    Elem* addLinElem(std::string& s){
        Elem* tmp = new Elem;
        tmp->data = s;
        tmp->next = nullptr;
        return tmp;
    }

    void printer(Elem* ptr){
        while(ptr){
            std::cout << ptr->data << ' ';
            ptr = ptr->next;
        }
        std::cout << '\n';
        std::cout << "Correct!\n";
    }

    void deleter(Node* tmp){
        if(tmp->next){
            deleter(tmp->next);
        }
        if (std::holds_alternative<Node*>(tmp->data)){
            if (std::get<Node*>(tmp->data)){
                deleter(std::get<Node*>(tmp->data));
            }
        }
        delete tmp;
    }

    void listDeleter(Elem* tmp){
        if(tmp->next){
            listDeleter(tmp->next);
        }
        delete tmp;
    }
};

int main(int argc, char* argv[]) {
	if(argc == 1){
		std::cout << "Wrong expression!" << '\n';
		return 0;	
	}
	std::string s = "";
	int i = 1;
	while(argv[i]){
		s = s + std::string(argv[i]) + ' ';
		i++;
	}
	s.erase(s.length() - 1);
    	linkedList list(s);
    	return 0;
}






