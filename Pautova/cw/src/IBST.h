#ifndef IBINTREE_H
#define IBINTREE_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

#include "BinTreeNode.h"

template<typename Elem>
class BinTree{
public:

    BinTree(std::vector<Elem>& sequence){
        make_tree(sequence);
    }
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
    
    void set_E(Elem E){
        this->E = E;
    }

    void find(Elem E){
        //this->E = E;
        search(this->head);
        //return is_find;
    }
    void search(std::shared_ptr<BinTreeNode<Elem>>& cur){
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

    void print(){ //обход в ширину, вывод на экран
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

    std::shared_ptr<BinTreeNode<Elem>>& get_head(){
        return this->head;
    }
    int height(std::shared_ptr<BinTreeNode<int>>& cur){
        if(cur == nullptr){
            return 0;
        }
        if(height(cur->left) > (height(cur->right))){
            return height(cur->left)+1;
        }
        return height(cur->right)+1;
        //return ceil(log2(1 + n));
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

    void make_tree(std::vector<Elem> sequence){
        this->sequence = sequence;
        this->n = sequence.size();
        std::sort(this->sequence.begin(), this->sequence.end());
        this->head = make_node(this->n);
    }

    std::shared_ptr<BinTreeNode<Elem>> make_node(int n){
        if (n == 0){
            return nullptr;
        }
        std::shared_ptr<BinTreeNode<Elem>> cur = std::make_shared<BinTreeNode<Elem>>();
        cur->left = make_node(n/2);
        cur->data = this->sequence.front();
        this->sequence.erase(this->sequence.begin());
        cur->right = make_node(n - (n/2) - 1);
        return cur;
    }

    void back_tracking(std::shared_ptr<BinTreeNode<Elem>>& cur){ //обход ЛКП
        if (cur){
            back_tracking(cur->left);
            this->sequence.push_back(cur->data);
            back_tracking(cur->right);
        }
    }
};

#endif