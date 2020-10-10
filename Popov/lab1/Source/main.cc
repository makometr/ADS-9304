#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>



int main(int argc, char* argv[]){

    setlocale(LC_ALL, "ru");
    if(argc != 3){
        std::cout << "Неверное кол-во аргументов!" << std::endl;
        return 1;
    }

    std::ifstream test(argv[1]);
    std::ofstream result(argv[2]);

    if(!test){
        std::cout << "Файл " << argv[1] << " не может быть открыт на чтение!" << std::endl;
        return 1;
    }

    std::vector<int> myVector {};
    std::vector<std::string> logs;

    std::string strInput;
    getline(test, strInput);
    strInput.c_str();
    bool flag = 0;
    for(int i = 0; strInput[i] != '\0'; i++){
        if(isdigit(strInput[i])){
            if(flag){
                continue;
            }else{
                myVector.emplace_back(atoi(&strInput[i]));
                flag = 1;
            }
        }else{
            flag = 0;
        }
    }

    int deep = 0;
    
    for(int i = 0; i < myVector.size(); i++){
        logs.emplace_back(std::to_string(myVector[i]) + ' ');
    }
    logs.emplace_back("<- Начальный вектор\n");

    auto RF = [&myVector, &logs, &deep](size_t from, size_t size, auto&& RF){
        deep++;
        if(size == 0){
            deep--;
            return;
        }
        if(size > 2){
            RF(from + 2, size - 2, RF);
        }
        if(myVector[from] > myVector[from + 1]){
            std::swap(myVector[from], myVector[from + 1]);
        }
        std::string new_data{};
            for(int i = 0; i < myVector.size(); i++){
                new_data += std::to_string(myVector[i]);
            }
            logs.emplace_back("глубина[" + std::to_string(deep) + "] = " + std::move(new_data) + ' ' + '\n');
        deep--;
    };

    if(myVector.size() % 2){
        RF(0, myVector.size() - 1, RF);
    }else{
        RF(0, myVector.size(), RF);
    }

    for(const auto &str : logs){
        result << str;
    }

    test.close();
    result.close();

    return 0;
}