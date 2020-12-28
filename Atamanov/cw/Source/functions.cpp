#include "functions.h"

static bool HuffmanComparator(std::pair<std::string, int> a1, std::pair<std::string, int> a2){
    if(a1.second >= a2.second)
        return false;
    else
        return true;
}

void getListOfElem(std::map<char, int>& map, std::string::iterator iterator){ // Мапа используемых символов
    if(*iterator == '\0')
        return;
    while(*iterator != '\0') {
        if (map.find(*iterator) != map.end()) {
            map[*iterator]++;
        } else {
            map.insert({*iterator, 1});
        }
        iterator++;
    }
}

void getStringWithWeigh(std::map<char, int> stringMap, std::pair<std::string, int>& weightString){ // Строка с весами(отсортированная)
    auto iterBeg = stringMap.begin();
    auto iterEnd = stringMap.end();
    std::pair<char, int> max;
    std::map<char, int> finder;
    int flag;
    while(1){
        flag = 0;
        for(;iterBeg != iterEnd;iterBeg++){
            if(iterBeg->second > max.second && finder.find((*iterBeg).first) == finder.end()){
                max.first = (*iterBeg).first;
                max.second = (*iterBeg).second;
                flag = 1;
            }
        }
        iterBeg = stringMap.begin();
        if(flag == 1){
            weightString.first += max.first;
            weightString.second += max.second;
            finder.insert({max.first, max.second});
            max.second = 0;
            continue;
        }
        break;
    }
}

void getCodesFromHuffman(std::shared_ptr<BinTreeNode> huffmanTree, std::map<char, std::string>& codesHuffman, std::string code){//Заполнение мапы кодов Хаффмана
    if(huffmanTree == nullptr){
        return;
    }
    else{
        if(huffmanTree->data.first.length() == 1)
            codesHuffman.insert({huffmanTree->data.first[0], code});
        else{
            getCodesFromHuffman(huffmanTree->left, codesHuffman, code+'0');
            getCodesFromHuffman(huffmanTree->right, codesHuffman, code+'1');
        }
    }
}

void printTree(std::shared_ptr<BinTreeNode> tree, int level, std::string code, bool debug, bool left){
    if(level == 0)
        std::cout << "Head: " << tree->data.first << "(" << tree->data.second << ")" << "\n";
    else {
        for (int i = 1; i < level; i++) {
            std::cout << "|\t";
        }
        if(left)
            std::cout << "|--- L: \'" << tree->data.first << "\'(" << tree->data.second << ") Code = \'" << code << "\'" << "\n";
        else
            std::cout << "|--- R: \'" << tree->data.first << "\'(" << tree->data.second << ") Code = \'" << code << "\'" << "\n";
    }
    if(debug){
        if(tree->left && tree->right) {
            std::cout << "Узел со строкой " << tree->data.first << " и весом " << tree->data.second;
            std::cout << " делится на узел со строкой \'" << tree->left->data.first << "\' и весом " << tree->left->data.second << ", который идет в левое поддерево";
            std::cout << ", а также узел со строкой \'" << tree->right->data.first << "\' и весом " << tree->right->data.second << ", который идет в правое поддерево\n";
        }
    }
    if (tree->left)
        printTree(tree->left, level + 1, code + '0', debug, true);
    if (tree->right)
        printTree(tree->right, level + 1, code + '1', debug, false);
}


static bool HuffmanStringComparator(char a1, char a2){
    if(a1 >= a2)
        return false;
    else
        return true;
}

void printHuffman(std::pair<std::string, int> stringWithWeight, std::map<char, int> usingSymbols, bool debug){
    std::cout << "\n------------------------------------------------------------------------------------------------------\n";
    std::cout << "Ход алгоритма Хаффмана\n";
    std::pair<std::string, int> temp;
    std::vector<std::pair<std::string, int>> huffmanString;
    for(int i=1;i<=stringWithWeight.first.length();i++){
        temp = std::make_pair(stringWithWeight.first[stringWithWeight.first.length()-i], usingSymbols[stringWithWeight.first[stringWithWeight.first.length()-i]]);
        huffmanString.push_back(temp);
    }
    while(huffmanString.size() != 1){
        temp = std::make_pair(huffmanString[0].first+huffmanString[1].first, huffmanString[0].second+huffmanString[1].second);
        std::sort(temp.first.begin(), temp.first.end(), HuffmanStringComparator);

        for(int i=0;i<huffmanString.size();i++){
            if(i == huffmanString.size() - 1)
                std::cout << huffmanString[i].first << "(" << huffmanString[i].second << ")\n";
            else
                std::cout << huffmanString[i].first << "(" << huffmanString[i].second << "), ";
        }
        if(debug && huffmanString.size() != 2){
            std::cout << "Первые два узла: \'" << huffmanString[0].first << "\'(" << huffmanString[0].second << ") и \'" << huffmanString[1].first << "\'(" << huffmanString[1].second << ")";
            std::cout << " складываются вместе: складываются сами строки, сортируются в лексикографическом порядке, а также складываются их веса.\n";
            std::cout << "Получается узел \'" << temp.first << "\' с весом " << temp.second << "\n";
        }
        if(huffmanString.size() == 2) {
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator);
            break;
        }
        else {
            huffmanString.erase(huffmanString.begin(), huffmanString.begin() + 2);
            huffmanString.push_back(temp);
            std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator);
        }
    }
    if(debug){
        std::cout << "На последнем шаге оставшиеся два узла: " << huffmanString[0].first << "(" << huffmanString[0].second << ") и " << huffmanString[1].first << "(" << huffmanString[1].second << ")";
        std::cout << " складываются вместе: складываются сами строки, сортируются в лексикографическом порядке, а также складываются их веса.\n";
        std::cout << "Получается узел " << temp.first << " с весом " << temp.second << ", который и является головой полученного дерева\n";
    }
    std::sort(huffmanString.begin(), huffmanString.end(), HuffmanComparator);
    std::cout << huffmanString[0].first << "(" << huffmanString[0].second << ")\n\n";
}

void printCodeTable(std::map<char, std::string> codes){
    auto checker = codes.end();
    checker--;
    for(auto i = codes.begin();i != codes.end(); i++) {
        if (i == checker)
            std::cout << i->first << "(" << i->second << ")\n";
        else
            std::cout << i->first << "(" << i->second << "), ";
    }
}

std::map<std::string, char> getCodesFromFile(const std::string& fileName){
    std::map<std::string , char> codes;
    char symbol;
    std::string temp;
    std::string code;
    auto iterBeg = temp.begin();
    std::ifstream file;
    file.open(fileName);
    if(!file.is_open()){
        std::cout << "Error: Undeclared codeFile";
        exit(EXIT_FAILURE);
    }
    while(!file.eof()){
        std::getline(file, temp);
        iterBeg = temp.begin();
        symbol = *iterBeg;
        iterBeg += 2;
        while(*iterBeg != ';') {
            code += *iterBeg;
            iterBeg++;
        }
        codes.insert({code, symbol});
        code.clear();
        temp.clear();
    }
    file.close();
    return codes;
}

void encode(std::string::iterator encodeString, std::string& shannonString, std::string& huffmanString, std::shared_ptr<BinTreeNode>& shannonTree, std::shared_ptr<BinTreeNode>& huffmanTree) {
    std::map<char, int> map;//Мапа с используемыми символами и их весами
    std::map<char, std::string> codesShannon, codesHuffman; //Коды для расшифровки
    std::pair<std::string, int> stringWithWeight; //Строка с общим весом символов
    std::string code; //Служебная переменная для передачи в функцию
    std::string outputShannon, outputHuffman; //Строка для вывода

    //Получение деревьев и файлов с кодами
    getListOfElem(map, encodeString);
    getStringWithWeigh(map, stringWithWeight);
    shannonTree = shannonTree->getShannonFanoTree(stringWithWeight, map, codesShannon, code);
    huffmanTree = huffmanTree->getHuffmanTree(stringWithWeight, map);
    getCodesFromHuffman(huffmanTree, codesHuffman, code);

    //Вывод деревьев и "пояснения за алгоритмы
    //------------------------------------------------------------------------------------------------------------------
    std::cout << "Исходные символы в кодируемом тексте и их веса:\n";
    auto checker = map.end();
    checker--;
    for (auto i = map.begin(); i != map.end(); i++) {
        if (i == checker)
            std::cout << i->first << "(" << i->second << ")\n";
        else
            std::cout << i->first << "(" << i->second << "), ";
    }
    std::cout << "Строка, полученная сложением всех символов, поседующей сортировки, и сложении их весов\n";
    std::cout << stringWithWeight.first << "(" << stringWithWeight.second << ")\n\n";
    std::cout << "Построение дерева Шано-Феннона\n";
    printTree(shannonTree, 0, code, true, false);
    std::cout << "Полученное дерево:\n";
    printTree(shannonTree, 0, code, false, false);
    std::cout << "Полученная таблица кодов для символов:\n";
    printCodeTable(codesShannon);
    printHuffman(stringWithWeight, map, true);
    std::cout << "Дерево Хаффмана, полученное при работе алгоритма Хаффмана\n";
    printTree(huffmanTree, 0, code, false, false);
    std::cout << "Полученная таблица кодов для символов:\n";
    printCodeTable(codesHuffman);
    std::cout
            << "------------------------------------------------------------------------------------------------------\n";
    //------------------------------------------------------------------------------------------------------------------

    std::cout << "Шифрование:\n";
    std::cout
            << "Шифрование происходит путем обращения к кодам, созданным ранее. Берется символ, её код ищется в таблице и заменяется в тексте на этот символ\n";
    std::string demonstrate;
    std::cout << "С помощью таблицы Фано-Шеннона:\n";
    auto temp = encodeString;
    auto save = encodeString;
    for (; *encodeString != '\0'; encodeString++) {
        temp = encodeString;
        for (; *temp != '\0'; temp++)
            demonstrate += *temp;
        std::cout << demonstrate << "\n";
        std::cout << "Текущий символ: " << *encodeString << " ,его код: " << codesShannon[*encodeString] << "\n";
        outputShannon += codesShannon[*encodeString];
        demonstrate.clear();
        demonstrate += outputShannon;
    }

    std::cout << "\nС помощью таблицы Хаффмана:\n";
    encodeString = save;
    demonstrate.clear();
    for (; *encodeString != '\0'; encodeString++) {
        temp = encodeString;
        for (; *temp != '\0'; temp++)
            demonstrate += *temp;
        std::cout << demonstrate << "\n";
        std::cout << "Текущий символ: " << *encodeString << " ,его код: " << codesHuffman[*encodeString] << "\n";
        outputHuffman += codesHuffman[*encodeString];
        demonstrate.clear();
        demonstrate += outputHuffman;
    }
    std::cout << "Окончательная закодированная строка:\n";
    std::cout << outputShannon << "\n";
    std::cout
            << "------------------------------------------------------------------------------------------------------\n";

    //Формирование файлов с кодами для декодирования
    std::ofstream outputShannonFile, outputHuffmanFile;
    outputShannonFile.open("./CodesShannon.txt");
    outputHuffmanFile.open("./CodesHuffman.txt");
    auto iterBeg = codesShannon.begin();
    for (; iterBeg != codesShannon.end(); iterBeg++)
        outputShannonFile << iterBeg->first << ":" << iterBeg->second << ";\n";
    iterBeg = codesHuffman.begin();
    for(;iterBeg != codesHuffman.end(); iterBeg++)
        outputHuffmanFile << iterBeg->first << ":" << iterBeg->second << ";\n";
    outputShannonFile.close();
    outputHuffmanFile.close();

    std::cout << "Декодирование:\n";
    std::map<std::string, char> decodesShannon = getCodesFromFile("./CodesShannon.txt");
    std::map<std::string, char> decodesHuffman = getCodesFromFile("./CodesHuffman.txt");
    std::cout << "Декодирование происходит в порядке, обратном кодированию: код заменяется соответствующим символом\n";

    std::cout << "С помощью таблицы Шеннона-Фано:\n";
    auto decodeIter = outputShannon.begin();
    demonstrate.clear();
    std::string output;
    for (; decodeIter != outputShannon.end(); decodeIter++) {
        temp = decodeIter;
        for(;*temp != '\0'; temp++)
            demonstrate += *temp;
        while (true) {
            code += *decodeIter;
            if (decodesShannon.find(code) != decodesShannon.end())
                break;
            else {
                decodeIter++;
                continue;
            }
        }
        std::cout << demonstrate;
        std::cout << "\nТекущий код: \'" << code << "\', символ, соответствующий коду: \'" << decodesShannon[code] << "\'\n";
        output += decodesShannon[code];
        demonstrate.clear();
        demonstrate += output;
        code.clear();
    }
    std::cout << "Окончательный вариант:\n" << output << "\n";

    std::cout << "\nС помощью таблицы Хаффмена:\n";
    decodeIter = outputHuffman.begin();
    demonstrate.clear();
    output.clear();
    for (; decodeIter != outputHuffman.end(); decodeIter++) {
        temp = decodeIter;
        for(;*temp != '\0'; temp++)
            demonstrate += *temp;
        while (true) {
            code += *decodeIter;
            if (decodesHuffman.find(code) != decodesHuffman.end())
                break;
            else {
                decodeIter++;
                continue;
            }
        }
        std::cout << demonstrate;
        std::cout << "\nТекущий код: \'" << code << "\', символ, соответствующий коду: \'" << decodesHuffman[code] << "\'\n";
        output += decodesHuffman[code];
        demonstrate.clear();
        demonstrate += output;
        code.clear();
    }
    std::cout << "Окончательный вариант:\n" << output << "\n";
}