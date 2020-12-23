#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <ctgmath>

class BinTree;

class Record{
public:
    std::vector<std::string> messages = {};
    std::vector<BinTree> history = {};
};

class BinTreeNode{
public:
    std::shared_ptr<BinTreeNode> left;
    std::shared_ptr<BinTreeNode> right;
    std::weak_ptr<BinTreeNode> parent;
    int index;
    friend class BinTree;
    BinTreeNode(std::shared_ptr<BinTreeNode> left, std::shared_ptr<BinTreeNode> right, const std::shared_ptr<BinTreeNode>& parent , int index): left(std::move(left)), right(std::move(right)), parent(parent), index(index)
    {
    }
};

class BinTree {
private:
    std::vector<int> elements;
    std::shared_ptr<BinTreeNode> head;

    void vecToBinTree(int numOfNodes, int& curIndex, std::shared_ptr<BinTreeNode> parent) {
        if (numOfNodes == 0) {
            return;
        }
        std::shared_ptr<BinTreeNode> curHead = std::make_shared<BinTreeNode>(nullptr, nullptr, parent, -1);
        if(numOfNodes == elements.size()){
            head = curHead;
        }
        if(curHead->parent.lock() != nullptr){
            if(curHead->parent.lock()->left == nullptr){
                curHead->parent.lock()->left = curHead;
            }else{
                curHead->parent.lock()->right = curHead;
            }
        }
        std::shared_ptr<BinTreeNode> globalHead = curHead;
        while(globalHead->parent.lock() != nullptr){
            globalHead = globalHead->parent.lock();
        }
        BinTree currentState(elements, globalHead);
        std::stringstream stringStream;
        stringStream << "Creating Node " << "\n" << "Current Element: " << elements[curIndex];
        std::string msg = stringStream.str();
        stringStream.str(std::string());
        record->messages.emplace_back(msg);
        record->history.push_back(currentState);
        vecToBinTree(numOfNodes / 2, curIndex, curHead);
        curHead->index = curIndex;
        stringStream << "Adding node: " << elements[curIndex] << "\n" << "Current Element: " << elements[curIndex];
        BinTree currentState2(elements, globalHead);
        msg = stringStream.str();
        stringStream.str(std::string());
        record->messages.emplace_back(msg);
        record->history.push_back(currentState2);
        curIndex++;
        vecToBinTree(numOfNodes - numOfNodes / 2 - 1, curIndex, curHead);
    }

    std::shared_ptr<BinTreeNode> copyBinTree(const std::shared_ptr<BinTreeNode> &otherHead, const std::shared_ptr<BinTreeNode> &headParent) {
        if (otherHead == nullptr) {
            return nullptr;
        }

        if (otherHead == head) {
            return head;
        }

        std::shared_ptr<BinTreeNode> curHead = std::make_shared<BinTreeNode>(nullptr, nullptr, headParent,
                                                                             otherHead->index);
        if (otherHead->left != nullptr) {
            curHead->left = copyBinTree(otherHead->left, curHead);
        }

        if (otherHead->right != nullptr) {
            curHead->right = copyBinTree(otherHead->right, curHead);
        }

        return curHead;
    }

public:
    std::shared_ptr<Record> record;
    BinTree(std::vector<int> vec) {
        std::sort(vec.begin(), vec.end());
        elements = vec;
        int counter = 0;
        record = std::make_shared<Record>();
        vecToBinTree(elements.size(), counter, nullptr);
    }

    BinTree(std::vector<int>& vec, std::shared_ptr<BinTreeNode>& otherHead){
        elements = vec;
        record = std::make_shared<Record>();
        this->head = copyBinTree(otherHead, nullptr);
    }

    ~BinTree() = default;

    BinTree(const BinTree &other) {
        head = copyBinTree(other.head, nullptr);
        elements = other.elements;
    }

    BinTree &operator=(const BinTree &other) {
        head = copyBinTree(other.head, nullptr);
        elements = other.elements;
        return *this;
    }

    BinTree(BinTree &&other) {
        head = std::move(other.head);
        elements = std::move(other.elements);
    }

    BinTree &operator=(BinTree &&other) {
        head = std::move(other.head);
        elements = std::move(other.elements);
        return *this;
    }

    void insertElem(int data) {
        std::stringstream stringStream;
        stringStream << "Adding new element to array: " << data << "\nRebuilding tree...";
        std::string msg = stringStream.str();
        BinTree currentState(elements, head);
        elements.push_back(data);
        std::sort(elements.begin(), elements.end());
        record->history.push_back(currentState);
        record->messages.push_back(msg);
        int counter = 0;
        vecToBinTree(elements.size(), counter, nullptr);
    }
   void deleteElem(int data) {
        if(!find(head, data)){
            std::cout << "Element for delete not found" << "\n";
            return;
        }
        std::stringstream stringStream;
        stringStream << "Deleting element from array: " << data << "\nRebuilding tree...";
        std::string msg = stringStream.str();
        auto position = std::find(elements.begin(), elements.end(), data);
        BinTree currentState(elements, head);
        elements.erase(position);
        record->history.push_back(currentState);
        record->messages.push_back(msg);
        int counter = 0;
        vecToBinTree(elements.size(), counter, nullptr);
    }

    bool find(const std::shared_ptr<BinTreeNode> &curNode, int dataToFind) {
        if (curNode == nullptr) {
            return false;
        }
        if (dataToFind == elements[curNode->index]) {
            return true;
        }
        if (dataToFind < elements[curNode->index]) {
            return find(curNode->left, dataToFind);
        }
        return find(curNode->right, dataToFind);
    }

    void printLevelOrder(const std::shared_ptr<BinTreeNode> &curNode) {
        for (int d = 0; d < this->height(this->getHead()); d++) {
            printLevel(curNode, d);
            std::cout << "\n";
        }
    }

    void printLevel(const std::shared_ptr<BinTreeNode> &curNode, int level) {
        if (curNode == nullptr) {
            std::cout << "_ ";
            return;
        }
        if (level == 0)
            std::cout << elements[curNode->index] << ' ';
        else {
            if (level > 0) {
                printLevel(curNode->left, level - 1);
                printLevel(curNode->right, level - 1);
            }
        }
    }


    std::shared_ptr<BinTreeNode> getHead() {
        return head;
    }

    int height(const std::shared_ptr<BinTreeNode> &curNode) {
        if (curNode == nullptr) {
            return 0;
        }
        if (height(curNode->left) > (height(curNode->right))) {
            return height(curNode->left) + 1;
        }
        return height(curNode->right) + 1;
    }

    void drawTree(sf::RenderWindow &window, float size, float x, float y, const std::shared_ptr<BinTreeNode> &curNode) {
        sf::CircleShape node(35.f * size);
        node.setPosition(x, y);
        node.setFillColor(sf::Color(90, 127, 230));
        node.setOutlineThickness(3);
        node.setOutlineColor(sf::Color::Black);
        sf::Text text;
        sf::Font font;
        font.loadFromFile("./Fonts/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(24 * size);
        if(curNode->index == -1){
            text.setString("No");
            text.setPosition(x + (22 * size), y + (20 * size));
        }else {
            text.setString(std::to_string(elements[curNode->index]));
            if (abs(elements[curNode->index]) < 1000) {
                if (abs(elements[curNode->index]) < 10) {
                    text.setPosition(x + (28 * size), y + (20 * size));
                } else {
                    if (abs(elements[curNode->index]) < 100) {
                        text.setPosition(x + (22 * size), y + (20 * size));
                    } else {
                        text.setPosition(x + (16 * size), y + (20 * size));
                    }
                }
            } else {
                text.setPosition(x + (28 * size), y + (20 * size));
                text.setString("...");
            }
        }
        text.setFillColor(sf::Color::Black);
        sf::Text messageBox;
        if (curNode->left != nullptr) {
            for (int i = -3; i < 3; i++) {
                sf::Vertex line[] =
                        {
                                sf::Vertex(sf::Vector2f(x + (35 * size) + i, y + (35 * size)), sf::Color::Black),
                                sf::Vertex(sf::Vector2f(
                                        x -
                                        (pow(2, this->height(curNode) - 4) * 35 + 17) * size * this->height(curNode) +
                                        (35 * size) + i,
                                        y + (185 * size)), sf::Color::Black)
                        };
                window.draw(line, 2, sf::Lines);
            }
            drawTree(window, size, x - (pow(2, this->height(curNode) - 4) * 35 + 17) * size * this->height(curNode),
                     y + (150 * size), curNode->left);
        }
        if (curNode->right != nullptr) {
            for (int i = -3; i < 3; i++) {
                sf::Vertex line[] =
                        {
                                sf::Vertex(sf::Vector2f(x + (35 * size) + i, y + (35 * size)), sf::Color::Black),
                                sf::Vertex(sf::Vector2f(
                                        x +
                                        (pow(2, this->height(curNode) - 4) * 35 + 17) * size * this->height(curNode) +
                                        (35 * size) + i,
                                        y + (185 * size)), sf::Color::Black)
                        };
                window.draw(line, 2, sf::Lines);
            }
            drawTree(window, size, x + (pow(2, this->height(curNode) - 4) * 35 + 17) * size * this->height(curNode),
                     y + (150 * size), curNode->right);
        }
        window.draw(node);
        window.draw(text);
    }

    std::vector<int>& getElements(){
        return elements;
    }

    std::string getElementsString(){
        std::stringstream stringStream;
        stringStream << "Elements: ";
        for(size_t i = 0; i < getElements().size(); ++i)
        {
            if(i != 0)
                stringStream << " ";
            stringStream << getElements()[i];
        }
        std::string elementsString = stringStream.str();
        return elementsString;
    }
};

bool checkString(std::string& str){
    auto iterator = str.cbegin();
    while(iterator != str.cend()){
        if(*iterator == '-'){
            iterator++;
        }
        if(!isdigit(*iterator)){
            return false;
        }

        while(isdigit(*iterator)){
            iterator++;
        }

        if((*iterator != ' ') && (iterator != str.cend())){
            return false;
        }

        while(*iterator == ' '){
            iterator++;
        }

    }
    return true;
}

int main() {
    std::cout << "Enter elements of tree: ";
    std::string inString{};
    std::getline(std::cin, inString);
    std::vector<int> vecInt;
    if (!checkString(inString)) {
        std::cout << "Incorrect string\n";
        return 0;
    }

    if (!inString.empty()) {
        std::stringstream iss(inString);
        int number;
        while (iss >> number)
            vecInt.push_back(number);
    }

    std::sort(vecInt.begin(), vecInt.end());
    BinTree tree(vecInt);
    int elemToInsert;
    std::cout << "Enter element to add: ";
    std::cin >> elemToInsert;
    int elemToDelete;
    std::cout << "Enter element to delete: ";
    std::cin >> elemToDelete;
    std::cout << '\n';
    tree.insertElem(elemToInsert);
    tree.deleteElem(elemToDelete);
    tree.printLevelOrder(tree.getHead());
    sf::RenderWindow window;
    window.create(sf::VideoMode(2000, 1000), "Binary Tree");
    int index = 0;
    std::stringstream stringStream;
    std::string msg;
    sf::Font font;
    sf::Text messageBox;
    font.loadFromFile("./Fonts/arial.ttf");
    messageBox.setFont(font);
    messageBox.setCharacterSize(24);
    messageBox.setFillColor(sf::Color::Black);
    messageBox.setPosition(10,10);
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && index<tree.record->history.size()){
                    index++;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && index>0){
                    index--;
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(240,240,240));
        if(index >= tree.record->history.size()) {
            tree.drawTree(window, 1, 1000, 40, tree.getHead());
            stringStream << "Iteration: " << index+1 << "\n" << tree.getElementsString() << "\nFinal Tree\n";
            msg = stringStream.str();
            stringStream.str(std::string());
            messageBox.setString(msg);
            window.draw(messageBox);
        }else{
            tree.record->history[index].drawTree(window, 1, 1000, 40, tree.record->history[index].getHead());
            stringStream << "Iteration: " << index+1 << "\n" <<tree.record->messages[index] << "\n" << tree.record->history[index].getElementsString();
            msg = stringStream.str();
            stringStream.str(std::string());
            messageBox.setString(msg);
            window.draw(messageBox);
        }
        window.display();
    }
}
