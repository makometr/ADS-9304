
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#define SIZE 500

int main() {
    unsigned long long int val=0;
    std::ofstream file;
    file.open("tests_for_stats.txt");
    std::string str="";
    srand(time(nullptr));
    for(unsigned long long int i = 0; i < SIZE/3; i++){
        val+=3;
        if (val>=4000){
            val=0;
            file<<str;
            str="";
        }
        str+=char('a' + rand() % ('a' - 'z'));
        str+=char(' ' + rand() % (' ' - '@'));
        str+=char('A' + rand() % ('A' - 'Z'));
    }
    std::cout<<str;
    file<<str;
    file.close();

return 0;
}

