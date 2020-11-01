#include <iostream>
#include <string>
#include "Tree.h"


void createTree( std::string lkp, std::string lpk, char value, std::shared_ptr<Node> &BinTree)
{
    using NodePtr = std::shared_ptr<Node>;
    NodePtr leftBranch=std::make_shared<Node>();
    NodePtr rightBranch=std::make_shared<Node>();
    leftBranch= nullptr;
    rightBranch= nullptr;

    if (lpk.length() < 2){
        BinTree = std::make_shared<Node>();
        BinTree->value = value;
        return;
    }

    int index = lkp.find(value);
    std::string leftlkp = lkp.substr(0, index);
    std::string leftlpk = lpk.substr(0, index);
    std::string rightlkp = lkp.substr(index + 1);
    lpk = lpk.erase(lpk.length()-1, 1);
    std::string rightlpk = lpk.substr(index);
    if (index!= 0){
        createTree(leftlkp, leftlpk, leftlpk[leftlpk.size() - 1], leftBranch);
    }
    createTree(rightlkp, rightlpk, rightlpk[rightlpk.size() - 1],  rightBranch);
    BinTree=BinTree->consBT(value, leftBranch, rightBranch);
}
bool isCorrect(std::string lkp , std::string lpk ){
    if (lkp.length() != lpk.length())
        return false;
    int i = 0;
    int pos=0;
    while(lkp.length()>0){
        pos=lpk.find(lkp[0]);
        if (pos==-1){
            return false;
        }
        lpk.erase(pos,1);
        lkp.erase(i,1);
    }
    if (lpk.length() != 0 && lkp.length()!=0){
        return false;
    }
    return true;
}

int main(){


    std::string lkp;
    std::string lpk;
    std::cout << "Enter the nodes in the LEFT ROOT RIGHT order\n";
    std::getline(std::cin,lkp);
    std::cout << "Enter the nodes in the LEFT RIGHT ROOT order\n";
    std::getline(std::cin,lpk);
    if (!isCorrect(lkp, lpk)){
        std::cout<<"\nError: incorrect write of the tree!\n";
        return EXIT_FAILURE;
    }
    using NodePtr = std::shared_ptr<Node>;
    NodePtr MyBinTree=std::make_shared<Node>();
    createTree(lkp, lpk, lpk[lpk.size() - 1], MyBinTree);
    std::cout << " the nodes in the ROOT LEFT RIGHT order:" << "\n";
    MyBinTree->printKLP(MyBinTree);
    std::cout <<"\n";
    std::cout << "Picture of a Binary Tree:" << "\n";
    MyBinTree->printTree(MyBinTree,1);
    return 0;
}
