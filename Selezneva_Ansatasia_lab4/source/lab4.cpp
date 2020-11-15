#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

void PrintVector(const std::vector<int>& v){
    for (int x : v){
        std::cout << x << " ";
    }
    std::cout << '\n';
}

void ShellSort (int& n, std::vector<int>& v){
    int i, j, step;
    int tmp;
    int o = 1;
    for (step = n / 2; step > 0; step /= 2){
        for (i = step; i < n; i++) {
            tmp = v[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < v[j - step]) {
                    v[j] = v[j - step];
                }
                else break;
            }
            v[j] = tmp;
            std::cout << o << " шаг: ";
            PrintVector(v);
            o++;
        }
    }
}

bool isCorrect(const std::string str){
    size_t i = 0;
    if(str.at(0) == '-' && i != str.size()-1){
        ++i;
    }
    while(i < str.size()){
        if(isdigit(str.at(i))){
            ++i;
        }
        else {
            return false;
        }
    }
    return true;
}


int main() {
    std::vector<int> v;
    std::string x;
    int i = 0;
    do {
        std::cin >> x;
        if(isCorrect(x)){
            if(x.at(0) == '-'){
                std::string x_1 = x.substr(1,x.size()-1);
                v.push_back(-atoi(x_1.c_str()));
            }else{
                v.push_back(atoi(x.c_str()));
            }
            i++;
        }
    } while(getchar() != '\n');
    if(i == 0){
        return 0;
    }
    std::vector<int> v2 = v;
    ShellSort(i, v);
    sort(v2.begin(), v2.end());
    std::cout << "Результат сортировки из библиотеки algorithm: ";
    PrintVector(v2);
    if (v == v2){
        std::cout << "Результаты сортировок совпадают" << '\n';
    } else {
        std::cout << "Результаты сортировок не совпадают" << '\n';
    }

    return 0;
}
