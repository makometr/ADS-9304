#include "functions.h"

int main(int argc, char* argv[]){
        std::string encodeString;
        std::string encodedShannon, encodedHuffman;
        std::shared_ptr<BinTreeNode> shannonTree, huffmanTree;
        std::getline(std::cin, encodeString);

        auto iterBeg = encodeString.begin();
        encode(iterBeg, encodedShannon, encodedHuffman, shannonTree, huffmanTree);
    return 0;
}