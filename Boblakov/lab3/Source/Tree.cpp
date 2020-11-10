#include "Tree.h"
using NodePtr = std::shared_ptr<Node>;
bool Node::isNull(std::shared_ptr<Node> node){
    return (node == nullptr);
}

NodePtr Node::consBT(const char& x, std::shared_ptr<Node> leftBranch, std::shared_ptr<Node> rightBranch){
    NodePtr unitedNode=std::make_shared<Node>();
    unitedNode->value = x;
    unitedNode->left = std::move(leftBranch);
    unitedNode->right = std::move(rightBranch);
    return unitedNode;
}

void Node::printTree(std::shared_ptr<Node> node, int n){
    if (node!= nullptr) {
        std::cout << ' ' << node->value;
        if(!isNull(node->right)) {
            printTree (node->right,n+1);
        }
        else std::cout <<"\n";

        if(!isNull(node->left)) {
            for (int i=1;i<=n;i++){
                std::cout << "  ";
            }
            printTree (node->left,n+1);
        }
    }
    else {
        std::cout<<"Tree is empty!";
    }
}

NodePtr Node::copyTree(const NodePtr &head) {
    NodePtr NewHead = std::make_shared<Node>();
    if (head== nullptr){
        return nullptr;
    }
    NewHead->value=head->value;
    NewHead->left=copyTree(head->left);
    NewHead->right=copyTree(head->right);

    return NewHead;
}
NodePtr Node::moveTree(NodePtr &head) {
    NodePtr NewHead = std::make_shared<Node>();
    if (head== nullptr){
        return nullptr;
    }
    NewHead=head;
    head= nullptr;
    return NewHead;
}

Node::Node() {
    this->value='\0';
    this->right = nullptr;
    this->left = nullptr;
}

void Node::printKLP(NodePtr head) {
    if (head!= nullptr){
        std::cout<<head->value;
    }
    if(head->left!= nullptr){
        printKLP(head->left);
    }
    if (head->right!= nullptr){
        printKLP(head->right);
    }
}
//
//Node &Node::operator=(const NodePtr &other) {
//   *this=other->copyTree(other);
//    return *this;
//}
//
//Node::Node(std::shared_ptr<Node> head) {
//   *this=this->copyTree((const NodePtr &) head);
//}


//Node& Node::operator=(NodePtr &&other) {
//    this=std::move(other);
//    return this;
//}

