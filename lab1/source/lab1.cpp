#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

bool isCorrect(string& argument);
void Files_read_write(ifstream& in, ofstream& out, string& argument, string& result, vector<string> &logs, int& deep);
void RF(string& argument, string& result, vector<string> &logs, int& deep);

int main(int argc, char** argv){
    setlocale(LC_ALL,"ru");
    string argument;
    string result;
    vector<string> logs;
    int deep = 0;
    if (argc < 3){
        std::cout << "Команда для запуска программы: lab1 /path/to/input /path/to/output" << endl;
        return 1;
    }
    else{
        ifstream in(argv[1]);
        if (!in.is_open()){
            std::cout << "Не удалось открыть файл " << argv[1] << endl;
            return 1; 
        }
        ofstream out(argv[2]);
        if (!out.is_open()){
            std::cout << "Не удалось открыть файл " << argv[2] << endl;
            return 1;
        }
        Files_read_write(in, out, argument, result, logs, deep);
        in.close();
        out.close();
    }
    return 0;
}

bool isCorrect(string& argument){
    if (argument[argument.length()-1] == '/' || argument[0] == '/' || argument.empty())
        return false;
    size_t index = 0;
    while (argument.find("/", index) != string::npos){
        index = argument.find("/", index);
        if (argument[++index] == '/')
            return false;
    }
    return true;
}

void Files_read_write(ifstream& in, ofstream& out, string& argument, string& result, vector<string> &logs, int& deep){
    getline(in, argument);
    if (!isCorrect(argument)){
        cout << "Некорректно введен аргумент." <<endl;
        return;
    }
    RF(argument, result, logs, deep);
    out << "result = " << result << "\nГлубина:\n";
    for (const auto &str : logs)
        out << str;
}

void RF(string& argument, string& result, vector<string> &logs, int& deep){
    if (argument.empty()){
        return;
    }
    deep++;
    if (argument.find("/") != string::npos){
        size_t size = argument.find("/");
        result.insert(0, argument, 0 ,size);
        logs.emplace_back(string(deep-1,'.') + move(string(argument, 0, size)) + "\n");
        argument.erase(0, size+1);
        RF(argument, result, logs, deep);
    }
    else{
        result.insert(0, argument);
        logs.emplace_back(string(deep-1,'.') + argument + "\n");
        argument.clear();
        return;
    }
}