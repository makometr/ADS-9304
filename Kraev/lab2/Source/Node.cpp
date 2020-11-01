#include "Node.h"


Node::Node(std::string &str){
	std::string::const_iterator iter = str.begin();
	int n=0;
	
	while(*iter == ' ' || *iter == '\n' || *iter == '\t'){
		iter++;
	}
	if(*iter == '\0'){	
		this->value = nullptr;
		this->next = nullptr;
	}else{
		try{
			if(*iter < 48 || *iter > 57)
				throw 1;
		}catch(int){
			std::cerr << "ERROR: the hierarchical content is set incorrectly\n";
			exit(0);
		}
		std::string num;
		while(*iter != ' '){
			try{
        		if((*iter < 48 || *iter > 57) && *iter != '.')
            		throw 1;
    		}catch(int){
        		std::cerr << "ERROR: the hierarchical content is set incorrectly\n";
        		exit(0);
    		}
			if(*iter == '.'){
				this->number.push_back(stoi(num));
				iter++;
				num.clear();
			}else{
				num.push_back(*iter);	
				iter++;
			}
		}
		this->number.push_back(stoi(num));
		std::string text;
		try{
			while(*iter != '['){
				if(*iter == '\0')
					break;
				this->name.push_back(*iter);
				iter++;
			}
			if(*iter == '['){
				while(*iter != ']'){
					if(*iter == '\0')
						throw 1;
					text.push_back(*iter);
					iter++;
				}
				text.push_back(*iter);
				iter++;
				this->value = text;
				this->isKnot = false;
			}else{
				this->isKnot = true;
			}
		}catch(int){
			std::cerr << "ERROR:the hierarchical content is set incorrectly\n";
			exit(0);
		}
		this->value = text;
	}
}



void Node::print(){
	if(this->number.size() != 0 && this->name.size() != 0){
		int last=0;
		for(int i=0;i < this->number.size()-1;i++){
			std::cout << this->number[i] << '.';
			last++;
		}
		std::cout << this->number[last];
		std::cout << this->name;
		
		if(std::get_if<std::string>(&this->value))
			std::cout << std::get<std::string>(this->value);
		
		std::cout << '\n';
	}
}




Node::~Node(){};
