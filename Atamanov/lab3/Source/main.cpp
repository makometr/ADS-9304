#include "Forest.h"
#include <string>

int main() {
    std::string string;
    std::getline(std::cin, string);
    auto iterCheck = string.begin();
    std::string stringForest = getConvenientLine(iterCheck);
    std::vector <std::string> forestVector;
    auto iterator = stringForest.cbegin();
    if (!isCorrect(iterator)) {
        std::cout << "Is incorrect forest\n";
        exit(EXIT_FAILURE);
    }
	iterator = stringForest.cbegin();
	if(isEmpty(iterator)){
		std::cout << "Empty forest\n";
		return 0;
	}
	iterCheck = stringForest.begin();
    stringToVectorForest(iterCheck, forestVector);
    std::shared_ptr <Forest<std::string>> forest;
    forest = forest->getForest(forestVector);
    std::shared_ptr <Forest<std::string>> copyForest = std::make_shared<Forest<std::string>>();
    copyForest = copyForest->getForest(forestVector);
    std::shared_ptr <BinTreeNode<std::string>> binTree;
    binTree = binTree->convertForestToBinTree(copyForest);
    forest->printForest(forest);
	std::cout << "Binary tree\n";
    binTree->printBinTree(binTree, 0);
    forest->widthSearch(forest);
    return 0;
}
