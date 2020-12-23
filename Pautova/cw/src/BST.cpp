#include "BST.h"

BST::BST(std::vector<int>& sequence){
    this->head = nullptr;
    make_tree(sequence);
}

BST::BST(BST&& other){
    std::swap(other.head, this->head);
}
BST& BST::operator=(BST&& other){
    if (&other != this)
        this->head = std::move(other.head);
    return *this;
}

BST::BST(BST& other){
    this->head = copy(other.head);
}
BST& BST::operator=(BST& other){
    if (&other != this)
        this->head = copy(other.head);
    return *this;
}
std::shared_ptr<BinTreeNode<int>> BST::copy(std::shared_ptr<BinTreeNode<int>> cur){
    if (cur){
        std::shared_ptr<BinTreeNode<int>> node = std::make_shared<BinTreeNode<int>>();
        node->left = copy(cur->left);
        node->right = copy(cur->right);
        node->data = cur->data;
        return node;
    }
    return nullptr;
}
    
void BST::set_E(int E){
    this->E = E;
}

void BST::make_tree(std::vector<int> tree){
    this->sequence = tree;
    while(!sequence.empty()){
        insert(sequence.front());
        sequence.erase(sequence.begin());
    }
}

void BST::printBST(std::shared_ptr<BinTreeNode<int>>& cur){
	std::cout << '(';
    if (cur){
        std::cout << cur->data;
        printBST(cur->left);
        printBST(cur->right);
    }
    std::cout << ')';
}

void BST::insert(int data_to_insert){
    if (!this->head){
        this->head = std::make_shared<BinTreeNode<int>>();
        this->head->data = data_to_insert;
        return;
    }
    std::shared_ptr<BinTreeNode<int>> node_to_insert {this->head};
    while(true){
        if(data_to_insert <= node_to_insert->data){
            if(!node_to_insert->left){
                node_to_insert->left = std::make_shared<BinTreeNode<int>>();
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
                node_to_insert->right = std::make_shared<BinTreeNode<int>>();
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

void BST::find(int E){
    //this->E = E;
    search(this->head);
    //return is_find;
}
void BST::search(std::shared_ptr<BinTreeNode<int>>& cur){
        if (cur){
            if (cur->data == this->E){
                this->is_find = true;
                return;
            }
            else{
                if (this->is_find){
                    return;
                }
                if(this->E < cur->data)
                    search(cur->left);
                else
                    search(cur->right);
            }
        }
}

int BST::height(std::shared_ptr<BinTreeNode<int>>& cur){
        if(cur == nullptr){
            return 0;
        }
        if(height(cur->left) > (height(cur->right))){
            return height(cur->left)+1;
        }
        return height(cur->right)+1;
}

std::shared_ptr<BinTreeNode<int>>& BST::get_head(){
    return this->head;
}

bool BST::empty(){
    return (!this->head);
}

void BST::tracking(BST& tree){
    if (tree.get_head()){
        std::queue<std::shared_ptr<BinTreeNode<int>>> Q;
        std::shared_ptr<BinTreeNode<int>> cur = std::make_shared<BinTreeNode<int>>();
        Q.push(tree.get_head());
        int path_length = 0;
        while(!Q.empty()){
            cur = Q.back();
            if (cur->left){
                Q.push(cur->left);
            }
            if(cur->right){
                Q.push(cur->right);
            }
            path_length++;
            Q.pop();
        }
    }
}