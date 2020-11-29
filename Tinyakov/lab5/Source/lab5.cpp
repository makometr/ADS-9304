#include <iostream>
#include <memory>

#define RED "\033[1;31m"
#define BLACK "\033[1;30m"
#define BLUE "\033[1;34m"
#define NORMAL "\033[0m"

template<typename T>
class RedBlackTreeNode{
public:
    bool is_red = true;
    bool is_left = false;
    T data;
    std::shared_ptr<RedBlackTreeNode<T>> left{nullptr}, right{nullptr};
    std::weak_ptr<RedBlackTreeNode<T>> parent;
    RedBlackTreeNode() = default;

    RedBlackTreeNode(T& data){
        this->data = data;
    }
    
    RedBlackTreeNode(T&& data){
        this->data = data;
    }

    ~RedBlackTreeNode() = default;
    
    RedBlackTreeNode(const RedBlackTreeNode<T>& node){
        data = node.data;
        left = node.left;
        right = node.right;
        parent = node.parent;
        is_red = node.is_red;
        is_left = node.is_left;
    }

    RedBlackTreeNode& operator=(const RedBlackTreeNode<T>& node){
        if(&node == this) return *this;
        data = node.data;
        left = node.left;
        right = node.right;
        parent = node.parent;
        is_red = node.is_red;
        is_left = node.is_left;
        return *this;
    }
    
    RedBlackTreeNode(const RedBlackTreeNode<T>&& node){
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        is_red = node.is_red;
        is_left = node.is_left;
    }

    RedBlackTreeNode& operator=(const RedBlackTreeNode<T>&& node){
        if(&node == this) return *this;
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        is_red = node.is_red;
        is_left = node.is_left;
        return *this;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, RedBlackTreeNode<T>& node){
    os << "{data: " << node.data << "; is_red: " << node.is_red
       << "; is_left: " << node.is_left << "; left: ";
    if(node.left) os << node.left->data;
    else os << "nullptr";
    os << "; right: ";
    if(node.right) os << node.right->data;
    else os << "nullptr";
    os << "; parent: ";
    if(node.parent.lock()) os << node.parent.lock()->data;
    else os << "nullptr";
    os << ";}";
    return os;
}

template<typename T>
class RedBlackTree{
using NodePtr = std::shared_ptr<RedBlackTreeNode<T>>;
protected:
    NodePtr head{nullptr};

    bool IsBlackNode(NodePtr node){
        return (node == nullptr || !node->is_red);
    }

    bool IsRedNode(NodePtr node){
        return !IsBlackNode(node);
    }

    void Recolor(NodePtr node){
        if(!node->parent.lock()){
            node->is_red = false;
            return;
        }
        if(!node->parent.lock()->parent.lock()){
            auto parent = node->parent.lock();
            parent->is_red = false;
            return;
        }
        auto parent = node->parent.lock();
        auto grandparent = parent->parent.lock();
        auto uncle = (parent->is_left ? grandparent->right : grandparent->left);
        if(IsRedNode(parent) && IsRedNode(uncle)){
            parent->is_red = uncle->is_red = false;
            grandparent->is_red = true;
            Balance(grandparent);
        }else if(IsRedNode(parent)){
            parent->is_red = false;
        }
    }

    void SmallRotate(NodePtr node){
        if(!node) return;
        if(!node->parent.lock()) return;
        if(!node->parent.lock()->parent.lock()) return;
        auto parent = node->parent.lock();
        auto grandparent = parent->parent.lock(); 
        node->parent = grandparent;
        if(parent->is_left){
            grandparent->left = node;
            node->is_left = true;
            parent->right = node->left;
            if(node->left){
                node->left->is_left = false;
                node->left->parent = parent;
            }
            parent->parent = node;
            node->left = parent;
        }else{
            grandparent->right = node;
            node->is_left = false;
            parent->left = node->right;
            if(node->right){
                node->right->is_left = true;
                node->right->parent = parent;
            }
            parent->parent = node;
            node->right = parent;
        }
    }
        
    void BigRotate(NodePtr node){
        if(!node) return;
        if(!node->parent.lock()) return;
        if(!node->parent.lock()->parent.lock()) return;
        auto parent = node->parent.lock();
        auto grandparent = parent->parent.lock();
        auto uncle = (parent->is_left ? grandparent->right : grandparent->left);
        std::swap(parent->data, grandparent->data);
        if(parent->is_left){
            parent->left = parent->right;
            if(parent->left) parent->left->is_left = true;
            parent->right = uncle;
            if(uncle) uncle->parent = parent;
            grandparent->right = parent;
            parent->is_left = false;
            grandparent->left = node;
            node->parent = grandparent;
        }else{
            parent->right = parent->left;
            if(parent->right) parent->right->is_left = false;
            parent->left = uncle;
            if(uncle) uncle->parent = parent;
            grandparent->left = parent;
            parent->is_left = true;
            grandparent->right = node;
            node->parent = grandparent;
        }
    }

    void Rotate(NodePtr node){
        if(!node->parent.lock()) return;
        if(!node->parent.lock()->parent.lock()) return;
        auto parent = node->parent.lock();
        auto uncle = (parent->is_left ? parent->parent.lock()->right : 
                        parent->parent.lock()->left);
        if(IsRedNode(parent) && IsBlackNode(uncle)){
            if(node->is_left != parent->is_left){
                SmallRotate(node);
                BigRotate(parent);
                return;
            }else{
                BigRotate(node);
            }
        }
        return;
    }

    void Balance(NodePtr node){
        Rotate(node);
        Recolor(node);
    }

public:
    RedBlackTree() = default;
    ~RedBlackTree() = default;

    RedBlackTree(const RedBlackTree<T>& tree){
        auto Copy = [](NodePtr parent, NodePtr& dest, const NodePtr& src,  auto&& Copy)->void{
            if(src == nullptr) return;
            dest = std::make_shared<RedBlackTreeNode<T>>(src->data);
            dest->parent = parent;
            Copy(dest, dest->left, src->left, Copy);
            Copy(dest, dest->right, src->right, Copy);
        };
        Copy(nullptr, head, tree.head, Copy);
    }
    
    RedBlackTree& operator=(const RedBlackTree<T>& tree){
        if(&tree == this) return *this;
        auto Copy = [](NodePtr parent, NodePtr& dest, const NodePtr& src,  auto&& Copy)->void{
            if(src == nullptr) return;
            dest = std::make_shared<RedBlackTreeNode<T>>(src->data);
            dest->parent = parent;
            Copy(dest, dest->left, src->left, Copy);
            Copy(dest, dest->right, src->right, Copy);
        };
        Copy(nullptr, head, tree.head, Copy);
        return *this;
    }

    RedBlackTree(RedBlackTree<T>&& tree){
        head = std::move(tree.head);
    }
    
    RedBlackTree& operator=(RedBlackTree<T>&& tree){
        if(&tree == this) return *this;
        head = std::move(tree.head);
        return *this;
    }
    
    void Insert(T new_data){
        auto new_node = std::make_shared<RedBlackTreeNode<T>>(new_data);
        if(head == nullptr){
            head = new_node;
            Balance(new_node);
            return;
        }
        NodePtr cur = head;
        while(true){
            if(new_data == cur->data){
                cur->data = new_data;
                break;
            }
            if(new_data < cur->data){
                if(cur->left == nullptr){
                    cur->left = new_node;
                    new_node->parent = cur;
                    new_node->is_left = true;
                    break;
                }else{
                    cur = cur->left;
                }
            }
            if(new_data > cur->data){
                if(cur->right == nullptr){
                    cur->right = new_node;
                    new_node->parent = cur;
                    new_node->is_left = false;
                    break;
                }else{
                    cur = cur->right;
                }
            }
        }
        Balance(new_node);
    }
    
    void PrintData(std::ostream& os = std::cout){
        auto print = [&os](NodePtr node, auto&& print)->void{
            if(node == nullptr) return;
            print(node->left, print);
            os << node->data << " ";
            print(node->right, print);
        };
        print(head, print);
        os << "\n";
    }

    void Print(std::ostream& os = std::cout){
        int deep = 0;
        std::string tab = "";
        auto print = [&tab, &deep, &os](NodePtr node, auto&& print)->void{
            if(node == nullptr){
                os << BLACK << "nullptr ("<< deep+1 << ")\n" << NORMAL;
                return;
            }
            if(node->is_red) os << RED <<node->data << "\n" << NORMAL;
            else os << BLACK << node->data << "\n" << NORMAL;
            if(!node->is_red) deep++;
            os << BLUE << tab << "|    " << "\n" << tab << "|---" ;
            tab += "|    ";
            print(node->right, print);
            tab = tab.substr(0, tab.size() - 5);
            os << BLUE << tab << "|    " << "\n" << tab << "|---" ;
            tab += "     ";
            print(node->left, print);
            tab = tab.substr(0, tab.size() - 5);
            if(!node->is_red) deep--;
        };
        print(head, print);
        os << "\n";
    }

    int Find(T find_data){
        int count = 0;
        auto find = [&find_data, &count](NodePtr node, auto&& find)->void{
            if(node == nullptr) return;
            if(find_data == node->data) count++;
            if(find_data < node->data) find(node->left, find);
            else find(node->right, find);
        };
        find(head, find);
        return count;
    }

};

template<typename T>
std::ostream& operator<<(std::ostream& os, RedBlackTree<T>& rbt){
    rbt.Print(os);
    return os;
}


int main(){
    int count, find;
    RedBlackTree<int> rbt;
    std::cin >> count;
    for(int i = 0; i < count; i++){
        int temp;
        std::cin >> temp;
        rbt.Insert(temp);
        std::cout << rbt;
    }
    std::cin >> find;
    rbt.PrintData();
    std::cout << "Count of element: " << rbt.Find(find) << "\n";
    
    return 0;
}
