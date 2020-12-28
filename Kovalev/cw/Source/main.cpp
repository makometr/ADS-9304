#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <chrono>
#include <vector>
#include <fstream>
#include <algorithm>

static int counterInsert = 0;
static int deleterInsert = 0;
template <typename T>
class Node{
public:
    int counter;
    T data;
    std::shared_ptr<Node<T>> left {nullptr};
    std::shared_ptr<Node<T>> right {nullptr};
    Node(){
        counter = 0;
    }
};

template <typename T>
class BSTree {
public:

    std::shared_ptr<Node<T>> head {nullptr};

    BSTree() {

    }

    BSTree(std::string &input) {
        std::istringstream s(input);
        T elem;
        while (s >> elem) {
            searchAndInsert(elem, head);
        }
    }

    ~BSTree() = default;

    void searchAndInsert(T elem, std::shared_ptr<Node<T>>& ptr) {
        counterInsert++;
        if (!ptr) {
            ptr = std::make_shared<Node<T>>();
            ptr->data = elem;
            ptr->counter = 1;
        } else if (elem < ptr->data) {
            searchAndInsert(elem, ptr->left);
        } else if (elem > ptr->data) {
            searchAndInsert(elem, ptr->right);
        } else {
            ptr->counter++;
        }
    }

    void searchAndDelete(T elem, std::shared_ptr<Node<T>>& ptr){
        deleterInsert++;
        if(ptr){
            if(ptr == head && !ptr->left && !ptr->right){
                head = nullptr;
                return;
            }
            if(elem < ptr->data){
                searchAndDelete(elem, ptr->left);
            }else if (elem > ptr->data){
                searchAndDelete(elem, ptr->right);
            }else if (elem == ptr->data){
                if(!ptr->left && !ptr->right){
                    ptr = nullptr;//findParent(elem, head);
                }else if (ptr->right){
                    T leftSon = findMin(ptr->right, ptr->counter);
                    searchAndDelete(leftSon, head);
                    ptr->data = leftSon;
                }else if (ptr->left){
                    T rightSon = findMax(ptr->left, ptr->counter);
                    searchAndDelete(rightSon, head);
                    ptr->data = rightSon;
                }
            }
        }else{
            std::cout << "There is no element " << elem << " in tree.\n";
        }
    }

    T findMin(std::shared_ptr<Node<T>> p, int& ct){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->left){
            temp = temp->left;
        }
        ct = temp->counter;
        return temp->data;
    }

    T findMax(std::shared_ptr<Node<T>> p, int& ct){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->right){
            temp = temp->right;
        }
        ct = temp->counter;
        return temp->data;
    }
	
    void printBST(std::shared_ptr<Node<T>> bt, std::string str=""){
        if(!bt){
            return;
        }
        std::string cpyStr = str;
        std::cout << bt->data << '\n';
        if(bt->right){
            std::cout << str;
        }
        if(!bt->left && bt->right){
            std::cout << "\x1b[31m└▶ \x1b[0m";
        }
        if(bt->left && bt->right){
            std::cout << "\x1b[31m├▶ \x1b[0m";
        }
        if(bt->left){
            printBST(bt->right, str.append("\x1b[34m│ \x1b[0m"));
        }else{
            printBST(bt->right, str.append(" "));
        }
        if(bt->left){
            std::cout << cpyStr;
        }
        if(bt->left){
            std::cout << "\x1b[34m└▶ \x1b[m";
        }
        printBST(bt->left, cpyStr.append(" "));
    }
	/*
    void printBST(std::shared_ptr<Node<T>> bt,int level)
    {
        if(bt)
        {
            printBST(bt->left,level + 1);
            for(int i = 0; i< level; i++){
                std::cout<<"  ";
            }
            std::cout << bt->data << std::endl;
            printBST(bt->right,level + 1);
        }
    }
	*/
};

bool digitChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isdigit(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

bool charChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isalpha(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

class researchData{
    std::ofstream research1;
    std::ofstream research2;
    std::ofstream research3;
    std::ofstream research4;
    std::string name1 = "research_insertions_average.txt";
    std::string name2 = "research_insertions_worstCase.txt";
    std::string name3 = "research_deletions_average.txt";
    std::string name4 = "research_deletions_worstCase.txt";
public:

    void insertAverageResearch(int size = 262144){
        srand(time(0));
        research1.open(name1);
        std::vector<int> vec;
        auto* bt = new BSTree<int>;
        shuffle(size, vec);
        for(int i = 0; i < size; i++) {
            counterInsert = 0;
            bt->searchAndInsert(vec[i], bt->head);
            research1 << i << " " << counterInsert << "\n";
        }
        research1.close();
        delete bt;
    }

    void insertWorstResearch(int size = 16384){
        srand(time(0));
        research2.open(name2);
        std::vector<int> vec;
        auto* bt = new BSTree<int>;
        worstGenerator(size, vec);
        for(int i = 0; i < size; i++) {
            counterInsert = 0;
            bt->searchAndInsert(vec[i], bt->head);
            research2 << i << " " << counterInsert << "\n";
        }
        research2.close();
        delete bt;
    }

    void deleteAverageResearch(int size = 16384){
        srand(time(0));
        research3.open(name3);
        std::vector<int> vec;
        auto* bt = new BSTree<int>;
        shuffle(size, vec);
        for(int j = 0; j < size; j++){
            bt->searchAndInsert(vec[j], bt->head);
        }
        for(int i = 0; i < size; i++) {
            deleterInsert = 0;
            bt->searchAndDelete(vec[vec.size() - 1 - i], bt->head);
            research3 << size - 1 - i << " " << deleterInsert << "\n";
        }
        research3.close();
        delete bt;

    }

    void deleteWorstResearch(int size = 16384){
        srand(time(0));
        research4.open(name4);
        std::vector<int> vec;
        auto* bt = new BSTree<int>;
        worstGenerator(size, vec);
        for(int j = 0; j < size; j++){
            bt->searchAndInsert(vec[j], bt->head);
        }
        for(int i = 0; i < size; i++) {
            deleterInsert = 0;
            bt->searchAndDelete(vec[vec.size() - 1 - i], bt->head);
            research4 << size - 1 - i << " " << deleterInsert << "\n";
        }
        research4.close();
        delete bt;
    }

    void shuffle(int count, std::vector<int>& vec) {
        for(int i = 0; i < count; i++){
            vec.push_back(i);
        }
        int temp;
        for(int i = count - 1; i >= 1; i--) {
            int j = rand()%(count);// обменять значения data[j] и data[i]
            temp = vec[j];
            vec[j] = vec[i];
            vec[i] = temp;
        }
    }

    void worstGenerator(int count, std::vector<int>& vec){
        for (int i = 0; i < count; i++){
            vec.push_back(i);
        }
        std::sort(vec.begin(), vec.end());
    }
};

int main(int argc, char* argv[]) {
	if (argc < 4){
		std::cout << "Finished successful\n";
		return 0;
	}
    std::string input(argv[1]);
    std::string comm(argv[2]);
    std::string element(argv[3]);
    if(isdigit(input[0])) {
        if (digitChecker(input)) {
            BSTree<int> bts;
            std::istringstream s(input);
            int elem;
            while (s >> elem) {
                bts.searchAndInsert(elem, bts.head);
            }
            std::cout << "This is random binary tree from your data:\n\n";
            bts.printBST(bts.head);
            std::cout << "\n\n";
            std::istringstream n(element);
            int el;
            n >> el;
            while (true) {
                std::cout << "If you want insert element - type \"i\" and type element, what you want insert.\n";
                std::cout << "If you want delete element - type \"d\" and type element, what you want delete.\n";
                std::cout << "If you want exit program - type \"e\" .\n";    
                if (comm == "i") {
                    std::cout << "You chose inserting. Please, type integer number, what you want to insert:\n";
                    bts.searchAndInsert(el, bts.head);
                    std::cout << "Tree after inserting:\n\n";
                    bts.printBST(bts.head);
		    comm = "";
                    std::cout << "\n\n";
                } else if (comm == "d") {
                    std::cout << "You chose deleting. Please, type integer number, what you want to delete:\n";
                    bts.searchAndDelete(el, bts.head);
                    std::cout << "Tree after deleting:\n\n";
                    bts.printBST(bts.head);
    		    comm = "";
                    std::cout << "\n\n";
                } else if (comm == "") {
                    break;
                }
            }
        } else {
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }else if(isalpha(input[0])){
        if(charChecker(input)){
            BSTree<char> bts;
            std::istringstream s(input);
            char elem;
            while (s >> elem) {
                bts.searchAndInsert(elem, bts.head);
            }
            std::cout << "This is random binary tree from your data:\n\n";
            bts.printBST(bts.head);
            std::cout << "\n\n";
            char choose;
	    std::istringstream n(element);
            char el;
            n >> el;
            while(true){
                std::cout << "If you want insert element - type \"i\" and type element, what you want insert.\n";
                std::cout << "If you want delete element - type \"d\" and type element, what you want delete.\n";
                std::cout << "If you want exit program - type \"e\" .\n";
                if(comm == "i"){
                    std::cout << "You chose inserting. Please, type integer number, what you want to insert:\n";
                    bts.searchAndInsert(el, bts.head);
                    std::cout << "Tree after inserting:\n\n";
                    bts.printBST(bts.head);
		    comm = "";
                    std::cout << "\n\n";
                }else if(comm == "d"){
                    std::cout << "You chose deleting. Please, type integer number, what you want to delete:\n";
                    bts.searchAndDelete(el, bts.head);
                    std::cout << "Tree after deleting:\n\n";
                    bts.printBST(bts.head);
		    comm = "";
                    std::cout << "\n\n";            
                }else if (comm == ""){
                    break;
                }
            }
        }else {
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }
    std::cout << "Finished successful!\n";
    return 0;
}

