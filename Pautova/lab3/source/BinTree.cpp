#include "BinTree.h"

BinTree::BinTree(BinTree&& other){
    std::swap(other.head, this->head);
}
BinTree& BinTree::operator=(BinTree&& other){
    if (&other != this)
        this->head = std::move(other.head);
    return *this;
}

BinTree::BinTree(BinTree& other){
    this->head = copy(other.head);
}
BinTree& BinTree::operator=(BinTree& other){
    if (&other != this)
        this->head = copy(other.head);
    return *this;
}
std::shared_ptr<BinTreeNode> BinTree::copy(std::shared_ptr<BinTreeNode> cur){
    if (cur){
        std::shared_ptr<BinTreeNode> node = std::make_shared<BinTreeNode>();
        node->left = copy(cur->left);
        node->right = copy(cur->right);
        node->data = cur->data;
        return node;
    }
    return nullptr;
}
    
void BinTree::set_E(Elem E){
    this->E = E;
    this->path = 0;
    this->number_E = 0;
}

void BinTree::read_tree(std::string& tree){
    this->head = read_node(tree);
}

std::shared_ptr<BinTreeNode> BinTree::read_node(std::string& tree){
    std::shared_ptr<BinTreeNode> node = std::make_shared<BinTreeNode>();
    if(tree.length() < 3){
        return nullptr;
    }
    if (tree.length() == 3){
        node->left = nullptr;
        node->right = nullptr;
        node->data = tree[1];
        return node;
    }
    std::stack<Elem> Stack;
    int index = 2;
    int cur_index = index;
    while (cur_index < (int)tree.length()){
        if (tree[cur_index] == '('){
            Stack.push(tree[cur_index]);
         }
        if (tree[cur_index] == ')'){
            if (Stack.empty()){
                break;
            }
            Stack.pop();
        }
        cur_index++;
        if (Stack.empty()){
            cur_index--;
            break;
        }
    }
    std::string left, right;
    left.insert(0, tree, index, cur_index-index+1);
    right.insert(0, tree, cur_index+1, tree.length()-2-cur_index);
    node->left = read_node(left);
    node->right = read_node(right);
    node->data = tree[1];
    return node;
}

void BinTree::printBinTree(std::shared_ptr<BinTreeNode> cur){
	std::cout << '(';
    if (cur){
        std::cout << cur->data;
        printBinTree(cur->left);
        printBinTree(cur->right);
    }
    std::cout << ')';
}

void BinTree::back_tracking(std::shared_ptr<BinTreeNode> cur){ //обход ЛКП
    if (cur){
        this->path += 1;
        back_tracking(cur->left);
        //std::cout << cur->data << " path = " << this->path << "\n";
        if (cur->data == this->E){
            this->number_E++;
            this->paths.push_back(this->path);
        }
        this->path += 1;
        back_tracking(cur->right);
    }
    //else{
	    this->path -= 1; //std::cout << "() ";
    //}
}

void BinTree::insert(Elem data_to_insert){
    if (!this->head){
        this->head = std::make_shared<BinTreeNode>();
        this->head->data = data_to_insert;
        return;
    }
    std::shared_ptr<BinTreeNode> node_to_insert {this->head};
    while(true){
        if(data_to_insert <= node_to_insert->data){
            if(!node_to_insert->left){
                node_to_insert->left = std::make_shared<BinTreeNode>();
                node_to_insert->left->data = data_to_insert;
                node_to_insert->left->left = node_to_insert->left->right = nullptr;
                break; 
            }
            else{
                node_to_insert = node_to_insert->left;
                continue;
            }
        }
        else{
            if(!node_to_insert->right){
                node_to_insert->right = std::make_shared<BinTreeNode>();
                node_to_insert->right->data = data_to_insert;
                node_to_insert->right->left = node_to_insert->right->right = nullptr;
                break; 
            }
            else{
                node_to_insert = node_to_insert->right;
                continue;
            }
        }
    }
}

std::shared_ptr<BinTreeNode> BinTree::get_head(){
    return this->head;
}
int BinTree::get_number_E(){
    return this->number_E;
}
int BinTree::get_min_path(){
    int min_path = this->paths.back();
    this->paths.pop_back();
    while(!this->paths.empty()){
        if (min_path > this->paths.back()){
            min_path = this->paths.back();
        }
        this->paths.pop_back();
    }
    return min_path; 
}
