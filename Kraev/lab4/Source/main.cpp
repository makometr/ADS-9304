#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <iterator>

void swap(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void print(std::vector<int> vec, int i){
	for(int j = 0;j < vec.size();j++){
		if(j == i)
			std::cout << '[' << vec[j] << "] ";
		else
			std::cout << vec[j] << " ";
	}
	std::cout << '\n';
}

void cycle_sort(std::vector<int>& vec){
	int pos = 0;
	int pos0 = 0;
	for(int i = 0;i < vec.size();){
		
		print(vec, i);

		for(int j = 0;j < vec.size();j++){
			if(vec[j] <= vec[i])
				pos++;	
		}
		while((vec[pos-1] == vec[i]) && (pos-1 != i))
			pos--;

		if((pos-1) == i){
			i++;
		}else{
			swap(vec[pos-1], vec[i]);

		}
		pos = 0;
	}
}

std::vector<int> strtovec(std::string str){
	std::string num;
	std::vector<int> vec;
	for(std::string::const_iterator it = str.begin();it != str.end();it++){
		if(*it != ' '){
			num.push_back(*it);
		}
		if(*it == ' ' && num.size() != 0){
			vec.push_back(stoi(num));
			num.clear();
		}
	}
	if(num.size() != 0){
		vec.push_back(stoi(num));
		num.clear();
	}
	return vec;
}

void check(char* str){
	try{
        char* c = str;
        for(int i = 0;c[i] != '\0';i++){
            if((c[i] < 48 || c[i] > 57) && (c[i] != ' '))
                throw 1;
        }
    }catch(int){
        std::cout << "ERROR: values must be int\n";
        exit(0);
    }
}

int main(int argc, char** argv){
	check(argv[1]);
	std::vector<int> vec = strtovec((std::string)argv[1]);
	cycle_sort(vec);
	return 0;
}

