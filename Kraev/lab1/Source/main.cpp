#include <iostream>
#include <string>

#define ELEMS "<>{}()"

std::string isBrackets(const std::string &str);
bool isArray(std::string::const_iterator &it);
bool isList(std::string::const_iterator &it);
bool isElem(std::string::const_iterator &it);



std::string isBrackets(const std::string &str){
	if(str.size() == 0){
		return "incorrect";
	}
	for(std::string::const_iterator it = str.begin();it != str.end();it++){ 
		if(!isElem(it) && !isList(it)){
			return "incorrect";
		}
	}
	return "correct";
}


bool isArray(std::string::const_iterator &it){
	int n = 0;
	while(*it != ']'){
		if(isElem(it) || isList(it)){
			it++;
		}else{
			return false;
		}
		if(*it == '\0'){
			return false;
		}
		n++;
    }
	if(n>=1){
		return true;
	}else{
		return false;
	}
}

bool isList(std::string::const_iterator &it){
    if(*it == 'N'){
		return true;
	}
	if(*it == '['){
		it++;
		return isArray(it);	
	}
	return false;
}

bool isElem(std::string::const_iterator &it){
	std::string elems(ELEMS);
	for(int i = 0;i < elems.size();i++){
		if(*it == elems[i])
			return true;
	}
	return false;
}


int main(int argc, char* argv[]){
	std::cout << isBrackets(argv[1]) << '\n';
	return 0;
}
