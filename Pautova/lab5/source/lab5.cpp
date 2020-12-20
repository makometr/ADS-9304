#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

template<typename Elem>
class BinTreeNode{
public:
    Elem data;
    std::shared_ptr<BinTreeNode> left {nullptr};
    std::shared_ptr<BinTreeNode> right {nullptr};
};

template<typename Elem>
class BinTree{
public:
    BinTree() = default;
    ~BinTree() = default;

    BinTree(BinTree&& other){
        std::swap(other.head, this->head);
    }
    BinTree& operator=(BinTree&& other){
        if (&other != this)
            this->head = std::move(other.head);
        return *this;
    }

    BinTree(BinTree& other){
        this->head = copy(other.head);
    }
    BinTree& operator=(BinTree& other){
        if (&other != this)
            this->head = copy(other.head);
        return *this;
    }
    std::shared_ptr<BinTreeNode<Elem>> copy(std::shared_ptr<BinTreeNode<Elem>> cur){
        if (cur){
            std::shared_ptr<BinTreeNode<Elem>> node = std::make_shared<BinTreeNode<Elem>>();
            node->left = copy(cur->left);
            node->right = copy(cur->right);
            node->data = cur->data;
            return node;
        }
        return nullptr;
    }

    void make_tree(std::vector<Elem> sequence){
        set_sequence(sequence);
        this->head = make_node(this->n);
    }
    
    void printBinTree(std::shared_ptr<BinTreeNode<Elem>> cur){
        if (cur){
            printBinTree(cur->left);
            std::cout << cur->data << ' ';
            printBinTree(cur->right);
        }
    }

    void deleted(){
        back_tracking(get_head());
        if (this->head->data >= this->E)
            deleted_node_left();
        else
            deleted_node_right();
        this->head = make_node(this->n);
    }

    void tracking(){ //обход в ширину
        if (this->head){
            std::queue<std::shared_ptr<BinTreeNode<Elem>>> Q;
            std::stringstream lower_level;
            std::shared_ptr<BinTreeNode<Elem>> cur = std::make_shared<BinTreeNode<Elem>>();
            Q.push(this->head);
            int i = 1;
            int j = 0;
            int nodes_at_level = 0;
            int h = height();
            std::cout << '\n' << std::string(pow(2, h-i)+1, ' ');
            while(!Q.empty()){
                cur = Q.front();
                if (nodes_at_level == pow(2, i-1)){
                    i += 1;
                    j += 1;
                    std::cout << "\n\n";
                    if (i != h){
                        std::cout << std::string(pow(2, h-i), ' ');
                    }
                    nodes_at_level = 0;   
                }
                if (i != h || h == 1){
                    std::cout << cur->data << std::string(pow(2, h-j)+1, ' ');
                    nodes_at_level += 1;
                }
                else{
                    std::cout << lower_level.str();
                    break;
                }

                if (cur->left){
                    Q.push(cur->left);
                    if(i == h-1){
                        lower_level << cur->left->data << "  ";
                    }
                }
                else{
                    if(i == h-1){
                        lower_level << "*  ";
                    }
                }
                if(cur->right){
                    Q.push(cur->right);
                    if(i == h-1){
                        lower_level << cur->right->data << "  ";
                    }
                }
                else{
                    if(i == h-1){
                        lower_level << "*  ";
                    }
                }

                Q.pop();
            }
        } 
    }

    void back_tracking_search(std::shared_ptr<BinTreeNode<Elem>> cur){ //обход ЛКП
        if (cur){
            if (cur->data == this->E){
                this->is_find = true;
                return;
            }
            if(cur->data > this->E)
                back_tracking_search(cur->left);
            else
                back_tracking_search(cur->right);
        }
    }  

    bool find(Elem E){
        this->E = E;
        back_tracking_search(this->head);
        return is_find;
    }
    void set_sequence(std::vector<Elem> sequence){
        this->sequence = sequence;
        this->n = sequence.size();
    }
    std::shared_ptr<BinTreeNode<Elem>> get_head(){
        return this->head;
    }
    int height(){
        return ceil(log2(1 + n));
    }
    bool empty(){
        return !n;
    }

private:
    Elem E;
    bool is_find = false;
    int n; // количество узлов
    std::vector<Elem> sequence{};
    std::shared_ptr<BinTreeNode<Elem>> head;

    std::shared_ptr<BinTreeNode<Elem>> make_node(int n){
        if (n == 0){
            return nullptr;
        }
        std::shared_ptr<BinTreeNode<Elem>> cur = std::make_shared<BinTreeNode<Elem>>();
        cur->left = make_node(n/2);
        cur->data = sequence.front();
        sequence.erase(sequence.begin());
        cur->right = make_node(n - (n/2) - 1);
        return cur;
    }

    void back_tracking(std::shared_ptr<BinTreeNode<Elem>> cur){ //обход ЛКП
        if (cur){
            back_tracking(cur->left);
            this->sequence.push_back(cur->data);
            back_tracking(cur->right);
        }
    }

    void deleted_node_left(){
        for (int i = (n/2); i >= 0; i--){
            if (this->E == sequence[i]){
                sequence.erase(sequence.begin()+i);
                n -= 1;
                break;
            }
        }
    }
    void deleted_node_right(){
        for (int i = (n/2+1); i < n; i++){
            if (this->E == sequence[i]){
                sequence.erase(sequence.begin()+i);
                n -= 1;
                break;
            }
        }
    }
};

template<typename T>
std::vector<T> read(std::string& tree){
    std::stringstream ss(tree);
    std::vector<T> array{};
    T value;
    while(ss >> value){
        array.push_back(value);
        if (ss.peek() == ' '){
			ss.ignore();
		}
        if(ss.peek() == '\n'){
            break;
        }
    }
    std::sort(array.begin(), array.end());
    return array;
}

bool check_tree(std::string& argument);

int main(int argc, char** argv){
    std::string tree;
    std::string to_find;
    bool is_file = false;
    if (argc < 2){
        std::cout << "tree = ";
        std::getline(std::cin, tree);
    }
    else{
        std::ifstream in(argv[1]);
        if (in.is_open()){
            is_file = true;
            std::getline(in, tree);
            std::getline(in, to_find);
            std::cout << "tree = " << tree << "\n";
        }
        else{
            std::cout << "Faild to open " << argv[1] << std::endl;
            return 1;
        }
        in.close();
    }
    bool all_is_number = check_tree(tree);
    bool end = false;
    if (all_is_number){
        BinTree<int> bin_tree;
        bin_tree.make_tree(read<int>(tree));
        bin_tree.tracking();
        if (is_file){
            std::vector<int> data_to_find = read<int>(to_find);
            while (!end){
                if (data_to_find.empty() || bin_tree.empty()){
                    end = true;
                }
                else{
                    if (bin_tree.find(data_to_find.front())){
                        std::cout << "\nElement to find and to delete: " << data_to_find.front();
                        bin_tree.deleted();
                        bin_tree.tracking();
                    }
                    data_to_find.erase(data_to_find.begin());
                }                
            }
        }
        else{
            while(!end && !bin_tree.empty()){
                std::cout << "\nInput element to find or exit\nInput: ";
                std::getline(std::cin, to_find);
                if (to_find == "exit"){
                    end = true;
                }
                else{
                    if(bin_tree.find(std::stoi(to_find))){
                        bin_tree.deleted();
                        bin_tree.tracking();
                    }
                }
            }
        }     
    }
    else{
        BinTree<std::string> bin_tree;
        bin_tree.make_tree(read<std::string>(tree));
        bin_tree.tracking();
        if (is_file){
            std::vector<std::string> data_to_find = read<std::string>(to_find);
            while (!end){
                if (data_to_find.empty() || bin_tree.empty()){
                    end = true;
                }
                else{
                    if (bin_tree.find(data_to_find.front())){
                        std::cout << "\nElement to find and to delete: " << data_to_find.front();
                        bin_tree.deleted();
                        bin_tree.tracking();
                    }
                    data_to_find.erase(data_to_find.begin());
                }                
            }
        }
        else{
            while(!end && !bin_tree.empty()){
                std::cout << "\nInput element to find or exit\nInput: ";
                std::getline(std::cin, to_find);
                if (to_find == "exit"){
                    end = true;
                }
                else{
                    if(bin_tree.find(to_find)){
                        bin_tree.deleted();
                        bin_tree.tracking();
                    }
                }
            }
        } 
    }
    std::cout << std::endl;
    return 0;
}

bool check_tree(std::string& argument){
    auto iterator = argument.cbegin();
    while(iterator != argument.cend()){
        if(*iterator == '-'){
            iterator++;
        }
        if(!isdigit(*iterator)){
            return false;
        }
        while(isdigit(*iterator)){
            iterator++;
        }
        if((*iterator != ' ') && (iterator != argument.cend()) && (*iterator != '.')){
            return false;
        }
        while(*iterator == ' '){
            iterator++;
        }
    }
    return true;
}