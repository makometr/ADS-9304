#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main(int argc, char* argv []) {
    bool existence_E = false;
    bool existence_point = false;
    bool real = true;
    int i = 0;
    std::string str;
    auto Is_real_number = [&real, &str, &existence_E, &existence_point](int& i, auto&& Is_real_number)->void{
        if((str[i]=='+' || str[i]=='-') && i != (str.size()-1) && ( i==0 || str[i-1] == 'E') ) {
            ++i;
            Is_real_number(i, Is_real_number);
        }
        else if(isdigit(str[i]) != 0 ) {
            if(i == (str.size()-1)){}
            else {
            ++i;
            Is_real_number(i, Is_real_number);
            }
        }
        else if(str[i] == '.' && i != 0 && existence_point == false && str[i+1] != 'E' && i != (str.size()-1) ){
            existence_point = true;
            ++i;
            Is_real_number(i, Is_real_number);
        }
        else if(str[i] == 'E' && i != 0 && existence_E == false && count(str.begin()+i,str.end(),'.') == 0 && i != (str.size()-1) ){
            existence_E = true;
            ++i;
            Is_real_number(i, Is_real_number);
        }
        else
        {
            real = false;
        }
        
    };

    if(argc < 2) {
        getline(std::cin, str, '\n');
    }
    else{
        int m = 1;
        for(int n = 0; argv[m][n]; ++n){
            str.push_back(argv[m][n]);
        }
    }
    Is_real_number(i, Is_real_number);

    if(real == true) {
        std::cout << "The real number\n";
    }else {
        std::cout << "This is not real number\n";
    }
    return 0;
} 