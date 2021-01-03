#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <stdlib.h>
#include <time.h>

class node{
public:
    int value;
    int count;
    int level;
    node* left;
    node* right;
    node(): count(0), left(nullptr), right(nullptr){}
};


class tree{
    
    int max_lvl;

    void draw_line(int current_line, node* cur) {
        if(cur->level == current_line) {
            std::cout << " ";
            std::cout << cur->value;
        }
        if(cur->left != nullptr) draw_line(current_line, cur->left);
        if(cur->right != nullptr) draw_line(current_line, cur->right);
    }

    int inPKL(node *cur, std::ostream& stream) {
        if(!cur) {
            return 1;
        }
        if(inPKL(cur->right, stream)) {
            for(int i=0; i<(max_lvl-cur->level); i++) {
                //std::cout << '\n';
            }
        } else {
            for(int i=0; i < (2+cur->level*4); i++) {
                stream << " ";
            }
            stream << "/\n";
        }
        for(int i=0; i < (cur->level*4); i++) {
            stream << " ";
        }
        stream << cur->value << '\n';
        if(cur->left) {
            for(int i=0; i < (2+cur->level*4); i++) {
                stream << " ";
            }
            stream << "\\\n";
        }
        if(inPKL(cur->left, stream)) {
            for(int i=0; i<(max_lvl-cur->level); i++) {
                //std::cout << '\n';
            }
        }
        return 0;
    }

    void lkp(node* cur, std::ostream &outstream) {
        if(cur == nullptr) return;
        lkp(cur->left, outstream);
        outstream << cur->value << " ";
        lkp(cur->right, outstream);
    }

    void searchAndInsert(int elem, node*& ptr, int level) {
        if (ptr == nullptr) {
            ptr = new node;
            ptr->value = elem;
            ptr->count = 1;
            ptr->level = level;
            if(level > max_lvl) {
                max_lvl = level;
            }
        } else if (elem < ptr->value) {
            searchAndInsert(elem, ptr->left, level+1);
        } else if (elem > ptr->value) {
            searchAndInsert(elem, ptr->right, level+1);
        } else {
            ptr->count++;
        }
    }

    int searchAndDelete(int elem, node*& ptr) {
        if(ptr) {
            if(elem == ptr->value) {
                if(ptr->right) {
                    node* tmp = ptr->right;
                    node* tmp_par = ptr;
                    while(tmp->left) {
                        if(tmp_par == ptr) {
                            tmp_par = ptr->right;
                            tmp = tmp->left;
                            continue;
                        }
                        tmp_par = tmp;
                        tmp = tmp->left;
                    }
                    if(tmp_par == ptr) {
                        ptr->right = nullptr;
                    } else {
                        tmp_par->left = nullptr;
                    }
                    ptr->value = tmp->value;
                    ptr->count = tmp->count;
                    searchAndDelete(tmp->value, tmp);
                } else if(ptr->left) {
                    node* tmp = ptr->left;
                    node* tmp_par = ptr;
                    while(tmp->right) {
                        if(tmp_par == ptr) {
                            tmp_par = ptr->left;
                            tmp = tmp->right;
                            continue;
                        }
                        tmp_par = tmp;
                        tmp = tmp->right;
                    }
                    if(tmp_par == ptr) {
                        ptr->left = nullptr;
                    } else {
                        tmp_par->right = nullptr;
                    }
                    ptr->value = tmp->value;
                    ptr->count = tmp->count;
                    searchAndDelete(tmp->value, tmp);
                } else if(!ptr->left && !ptr->right) {
                    delete ptr;
                    ptr = nullptr;
                }
            } else if(elem < ptr->value) {
                searchAndDelete(elem, ptr->left);
            } else if(elem > ptr->value) {
                searchAndDelete(elem, ptr->right);
            }
            return 0;
        } else {
            return 1;
        }
    }

    void addlevel(node* cur) {
        if(!cur) {
            return;
        }
        cur->level++;
        addlevel(cur->left);
        addlevel(cur->right);
    }

    void klp(node *cur, std::ostream& stream) {
        if(!cur) {
            return;
        }
        stream << cur->value << " ";
        klp(cur->left, stream);
        klp(cur->right, stream);
    }

public:

    node *head;

    tree(std::string st): max_lvl(1), head(nullptr) {
        for(auto iter = st.begin(); iter!=st.end(); iter++) {
            char a = *iter;
            searchAndInsert(atoi(&a), head, 1);
        }
    }
    
    tree(int elem): max_lvl(1), head(nullptr) {
        searchAndInsert(elem, head, 1);
    }

    void horizontal() {
        for(int i = 1; i <= max_lvl; i++) {
            draw_line(i, head);
            std::cout << "\n";
        }
    }

    void LKP(std::ostream &outstream) {
        lkp(head, outstream);
        outstream << "\n";
    }

    void insertElem(int elem) {
        searchAndInsert(elem, head, 1);
    }

    void deleteElem(int elem) {
        searchAndDelete(elem, head);
    }

    void graphPKL(std::ofstream& stream) {
        inPKL(head, stream);
    }

    void graphPKL() {
        inPKL(head, std::cout);
    }

    void insertElemInRoot(int elem) {
        if(elem == head->value) {
            return;
        }
        deleteElem(elem);
        node *newhead = new node;
        newhead->count = 1;
        newhead->value = elem;
        newhead->level = 1;
        if(elem < head->value) {
            newhead->left = head->left;
            newhead->right = head;
            head->left = nullptr;
            addlevel(head);
        } else if(elem > head->value) {
            newhead->right = head->right;
            newhead->left = head;
            head->left = nullptr;
            addlevel(head);
        }
        head = newhead;
    }

    void KLP(std::ostream& stream) {
        klp(head, stream);
        stream << "\n";
    }

    void KLP() {
        klp(head, std::cout);
        std::cout << "\n";
    }
};

class control {
public:
    control() {}

    void generateTest(int count) {
        std::ofstream filetest;
        std::ofstream fileanswer;
        filetest.open("test.txt", std::ios_base::out);
        if(!filetest.is_open()) {
            std::cout << "test file does not opened\n";
            exit(0);
        }
        fileanswer.open("answer.txt", std::ios_base::out);
        if(!fileanswer.is_open()) {
            std::cout << "answer file does not opened\n";
            exit(0);
        }
        tree* sap = nullptr;
        for(int iter = 1; iter <= count; iter++) {
            if(rand()%2) {
                filetest << iter << ". Нарисуйте случайное БДП, составленное из ввода чисел: ";
                int j = rand()%100;
                sap = new tree(j);
                filetest << j << " ";
                for(int i = 0; i < 8; i++) {
                    j = rand()%100;
                    filetest << j << " ";
                    sap->insertElem(j);
                }
                filetest << "\n\n";
                filetest << "-------------------------------------\n";
                fileanswer << iter << ".\n";
                sap->graphPKL(fileanswer);
                fileanswer << "\n\n\n";
                fileanswer << "-------------------------------------\n";
            } else {
                filetest << iter << ". Сделайте КЛП обход по предоставленному дереву\n\n";
                int j = rand()%100;
                sap = new tree(j);
                for(int i = 0; i < 8; i++) {
                    j = rand()%100;
                    sap->insertElem(j);
                }
                sap->graphPKL(filetest);
                filetest << "-------------------------------------\n";
                fileanswer << iter << ". ";
                sap->KLP(fileanswer);
                fileanswer << "-------------------------------------\n";
            }
        } 
        delete sap;
        filetest.close();
        fileanswer.close();
    }
};

int main() {
    std::string st;
    srand(time(0));
    control* test = new control;
    /*
    std::getline(std::cin, st);
    tree sap(st);
    std::ofstream fname;
    fname.open("out.txt");
    sap.LKP(fname);
    fname.close();
    sap.graphPKL();
    */
    std::string a;
    std::cout << "Choose number of tasks (standart 5, \"n\" for programm shut down)\n";
    std::cin >> a;
    if(a == "n") {
        std::cout << "Stopping...\n";
        exit(0);
    }
    if(isdigit(a[0])) {
        test->generateTest(std::stoi(a));
    } else {
        test->generateTest(5);
    }
    std::cout << '\n';
    return 0;
}