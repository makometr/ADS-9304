#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

class node{
public:
    int value;
    int count;
    int level;
    node* left;
    node* right;
    node(): left(nullptr), right(nullptr) {}
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

    void lkp(node* cur, std::ostream &outstream) {
        if(cur == nullptr) return;
        lkp(cur->left, outstream);
        outstream << cur->value << " ";
        lkp(cur->right, outstream);
    }

public:

    node *head;

    tree(std::string st): head(nullptr), max_lvl(1) {
        for(auto iter = st.begin(); iter!=st.end(); iter++) {
            char a = *iter;
            if(!isdigit(a)) continue;
            searchAndInsert(atoi(&a), &head, 1);
        }
    }

    void searchAndInsert(int elem, node** ptr, int level) {
        if ((*ptr) == nullptr) {
            (*ptr) = new node;
            (*ptr)->value = elem;
            (*ptr)->count = 1;
            (*ptr)->level = level;
            if(level > max_lvl) max_lvl = level;
        } else if (elem < (*ptr)->value) {
            searchAndInsert(elem, &(*ptr)->left, level+1);
        } else if (elem > (*ptr)->value) {
            searchAndInsert(elem, &(*ptr)->right, level+1);
        } else {
            (*ptr)->count++;
        }
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
};

int main() {
    std::string st;
    std::getline(std::cin, st);
    tree sap(st);
    std::ofstream fname;
    fname.open("tree.txt");
    sap.LKP(fname);
    sap.horizontal();
    fname.close();
    return 0;
}