#include "Node.h"
#include "List.h"
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <unistd.h>


int main(int argc, char** argv){
	List list("Source/text.txt");

	int opt =0;
	std::vector<int> number, number2;
    std::string num;

	char* optString = "abcde";
	opt = getopt( argc, argv, optString );
    
	while( opt != -1 ) {
        switch( opt ) {
            case 'a':		// добавление элемента
				list.addElem(argv[2]);
				break;
                 
            case 'b':		// удаление элемента по номеру
				while(*argv[2] != '\0' ){
					if(*argv[2] != '.'){
						num.push_back(*argv[2]);
					}else{
						number.push_back(stoi(num));
						num.clear();
					}
					argv[2]++;
				}
				number.push_back(stoi(num));
				list.deleteElem(number);
				break;
                 
            case 'c':		// удаление элемента по названию
                list.deleteElem(argv[2]);
				break;
                 
            case 'd':		// изменение названия
                while(*argv[2] != '\0' ){
                    if(*argv[2] != '.'){
                        num.push_back(*argv[2]);
                    }else{
                        number.push_back(stoi(num));
                        num.clear();
                    }
                    argv[2]++;
                }
				number.push_back(stoi(num));
				list.changeName(number, argv[3]);
				break;
                 
            case 'e':  		// изменение номера
				while(*argv[2] != '\0' ){
                    if(*argv[2] != '.'){
                        num.push_back(*argv[2]);
                    }else{
                        number.push_back(stoi(num));
                        num.clear();
                    }
                    argv[2]++;
                }
				number.push_back(stoi(num));
				num.clear();
				while(*argv[3] != '\0' ){
                    if(*argv[3] != '.'){
                        num.push_back(*argv[3]);
                    }else{
                        number2.push_back(stoi(num));
                        num.clear();
                    }
                    argv[3]++;
                }
                number2.push_back(stoi(num));
				
				list.changeNumber(number, number2);
                break;
                 
            default:
                break;
        }
         
        opt = getopt( argc, argv, optString );
    }
	list.print();
	return 0;
}
