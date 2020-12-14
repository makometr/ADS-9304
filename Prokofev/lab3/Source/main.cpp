#include "iostream"
#include "string.h"
#include <fstream>
#include <memory>

class BinTree{
public:
    char value;
    std::shared_ptr<BinTree> left {nullptr};
    std::shared_ptr<BinTree> right {nullptr};
};


void drawTree(std::shared_ptr<BinTree> curNode, int level, int direction)
{
    if(curNode)
    {
        drawTree(curNode->right,level + 1, 1);
        for(int i = 0;i< level;i++) std::cout<<"    ";
        if(direction == 1) std::cout << "/ ";
        else if(direction == 2) std::cout << "\\ ";
        std::cout << curNode->value << std::endl;
        drawTree(curNode->left,level + 1, 2);
    }
}

void printTree(std::shared_ptr<BinTree> curNode) {
    if (!curNode) {
        return;
    }
    printTree(curNode->left);
    printTree(curNode->right);
    std::cout << curNode->value << ' ';
}

bool No_old(char a, char b, char* KLP_local)
{
    for(int i=0; KLP_local[i]&&(KLP_local[i]!=b); i +=2)
        if(KLP_local[i]==a) return false;
    return true;
}

void repair(std::shared_ptr<BinTree> current_node, char *LKP, char* KLP, int &i_main, int old_i)
{
    int i;
    i_main +=2;
    char exec;
    for(int j=0; j<2; j++)
    {
        exec = KLP[i_main];
        if(current_node->right==nullptr)
        for(i=old_i+2; (LKP[i])&&No_old(LKP[i], exec, KLP); i +=2)
        {
            if(exec == LKP[i])
            {
                current_node->right = std::make_shared<BinTree>();
                current_node->right->value = exec;
                repair(current_node->right, LKP, KLP, i_main, i);
                break;
            }
        }
        if(current_node->left==nullptr)
        for(i=old_i-2; ((i>-2))&&No_old(LKP[i], exec, KLP); i -=2)
        {
            if(exec == LKP[i])
            {
                current_node->left = std::make_shared<BinTree>();
                current_node->left->value = exec;
                repair(current_node->left, LKP, KLP, i_main, i);
                break;
            }
        }
    }
}



int main(int argc, char* argv[])
{
    std::string input1, input2;
    std::ifstream in("input.txt");
    getline(in, input1);
    getline(in, input2);
    char KLP[50];
    char LKP[50];
    strcpy(KLP, input1.c_str());
    strcpy(LKP, input2.c_str());
    
    if(strlen(KLP)==strlen(LKP))
    {
    int i_glav = 0;
    int i = 0;
    std::shared_ptr<BinTree> My_Tree=std::make_shared<BinTree>();
    My_Tree->value=KLP[0];
    for(i=0; LKP[i]&&(LKP[i]!=My_Tree->value);  i +=2);
    repair(My_Tree, LKP, KLP,  i_glav, i);
    if((i_glav-1)==strlen(KLP)) {
                                std::cout << "Picture of tree:\n";
                                drawTree(My_Tree, 0, 0);
                                std::cout << "Tree in LPK:\n";
                                printTree(My_Tree);
                                std::cout << std::endl;
                                }
    else std::cout << "Tree is incorrect";
    } else std::cout << "Tree is incorrect";
    return 0;
}
