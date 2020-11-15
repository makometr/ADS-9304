#include "customQsort.h"
#include <iostream>



std::vector<int> convert(std::string &strValue){

    std::vector<int> arrDigit {};
    strValue.c_str();
    bool flag1 = 0;
    bool flag2 = 0;
    for(size_t i = 0; strValue[i] != '\0'; i++){
        if(isdigit(strValue[i])){
            if(flag1){
                continue;
            }else{
                arrDigit.emplace_back(atoi(&strValue[i]));
                flag1 = 1;
            }
        }else if(strValue[i] == '-'){
            flag2 = 1;
        }else{
            flag1 = 0;
            if(flag2){
                arrDigit[arrDigit.size() - 1] -= (arrDigit.back() * 2);
                flag2 = !flag2;
            }
        }
    }
    if(!arrDigit.size()){
        arrDigit.clear();
    }
    
    return arrDigit;
}



void customQsort(std::vector<int> &arrDigit){

    size_t l = 0;                       // left index
    size_t r = arrDigit.size() - 1;     // right index

    auto PR = [&arrDigit](int l, int r, auto&& PR){

        int left = l;
        int right = r;
        int base = arrDigit[(l + r) / 2];

        if(l >= r){
            return;
        }

        while(left < right){
            
            while(arrDigit[left] < base){
                ++left;
            }
            while(arrDigit[right] > base){
                --right;
            }
            if(left <= right){
                if(left != right){
                    for(const auto &str : arrDigit){
                        std::cout << str << ' ';
                    }
                    std::swap(arrDigit[left], arrDigit[right]);
                    std::cout << "\t->\tSwap " << arrDigit[left] << '[' << right << ']' << " and " << arrDigit[right] << '[' << left << ']' << "\t->\t";
                    for(const auto &str : arrDigit){
                        std::cout << str << ' ';
                    }
                    std::cout << '\n';
                }
                ++left;
                --right;
            }
            
            PR(l, right, PR);
            PR(left, r, PR);
        }
    };

    PR(l, r, PR);
    
}