#include <iostream>
#include <memory>

class Citizen{
	public:
	std::string name;
	std::string kids_list;
	Citizen(std::string name = "", std::string  kids_list = ""){
		this->name = name;
		this->kids_list = kids_list;
	}

	bool are_relatives(Citizen& B, std::shared_ptr<Citizen[]> array,int length, int deep){
		if(name == B.name){
			return false;
		}
		if((B.kids_list.find(name) != std::string::npos) || (kids_list.find(B.name) != std::string::npos)){
			return true;
		}
		if(deep == length){
			return false;
		}
		for(int i = 0; i < length; i++){
			if((this->are_relatives(array[i], array, length, deep+1)) && (array[i].are_relatives(B, array, length, deep+1))){
						return true;
					}
		}
		return false;
	}	
};

int main(){
	int number;
	std::cin >> number;
	auto array = std::shared_ptr<Citizen[]>(new Citizen[number]);
	for( int i = 0; i < number; i++ ) {
		std::cin >> array[i].name;
		getline(std::cin,array[i].kids_list,'\n');
	}
	for( int i = 0; i < number; i++ ) {
		for( int j = i; j < number; j++ ) {
			if(array[i].are_relatives( array[j], array, number, 0)){
				std::cout << array[i].name << " - " << array[j].name << "\n";
			}
		}
	}
	return 0;
}
