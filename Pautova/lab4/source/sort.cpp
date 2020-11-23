#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

template<typename T>
void print(std::vector<T>& array,int start ,int end){
    for (int i = start; i < end; i++)
        std::cout << array[i] << " ";
    std::cout << "\n";
}

template<typename T>
void Merging(std::vector<T> vec1, std::vector<T> vec2, std::vector<T>& array, int pos){
    int i = 0;
    int j = 0;
    int index = pos;
    while(i < vec1.size()){
        if (vec1[i] < vec2[j]){
            array[index] = vec1[i];
            i += 1;
            index += 1;
        }
        else{
            array[index] = vec2[j];
            j += 1;
            index += 1;
            if (j == vec2.size())
                break;
        }
    }
    if (i < vec1.size()){
        while (i < vec1.size()){
            array[index] = vec1[i];
            index += 1;
            i += 1;
        }
    }
    if (j < vec2.size()){
        while (j < vec2.size()){
            array[index] = vec2[j];
            index += 1;
            j += 1;
        }
    }
    std::cout << "merging = ";
    print<T>(array, pos,index);

    std::cout << "array after merging = ";
    print(array, 0, array.size());
    std::cout << '\n';
}

template<typename T>
void MergeSort(std::vector<T>& array){
    std::vector<T> vec1{};
    std::vector<T> vec2{};
    bool end = false;
    int iteration = 0;
    do{
        int pos = 0;
        std::cout << "Iteration = " << iteration << "\n";
        std::cout << "array befor merging = ";
        print(array, 0, array.size());
        int i = 0;
        while(i < array.size()){
            vec1.clear();
            vec2.clear();

            vec1.push_back(array[i++]);
            while (array[i-1] <= array[i] && i < array.size()){
                vec1.push_back(array[i]);
                i += 1;
            }

            if (vec1.size() == array.size()){
                end = true;
                break;
            }
            else{
                if (i == array.size())
                    break;
            }

            vec2.push_back(array[i++]);
            while(array[i-1] <= array[i] && i < array.size()){
                vec2.push_back(array[i]);
                i += 1;   
            }

            std::cout << "vec1 = ";
            print<T>(vec1, 0, vec1.size());
            std::cout << "vec2 = ";
            print<T>(vec2, 0, vec2.size());
            
            if (vec1.size() >= vec2.size())
                Merging<T>(vec1, vec2, array, pos);
            else
                Merging<T>(vec2, vec1, array, pos);

            pos += vec1.size() + vec2.size();
            
        }
        iteration += 1;
    }while(!end);
}

template<typename T>
std::vector<T> read(std::string& argument){
    std::stringstream ss(argument);
    std::vector<T> array{};
    T value;

    while(ss >> value){
        array.push_back(value);
        if (ss.peek() == ' '){
			ss.ignore();
		}
        if(ss.peek() == '\n'){
            break;
        }
    }
    return array;
}

bool check_argument(std::string& argument);

int main(int argc, char** argv){
    std::string argument;
    if (argc < 2){
        std::cout << "array = ";
        std::getline(std::cin, argument);
        std::cout << '\n';
    }
    else{
        std::ifstream in(argv[1]);
        if (in.is_open()){
            std::getline(in, argument);
            std::cout << "array = " << argument << "\n\n";
        }
        else{
            std::cout << "Faild to open " << argv[1] << std::endl;
            return 1;
        }
        in.close();
    }
    bool all_is_number = check_argument(argument);

    std::vector<std::string> array_string{};
    //std::vector<float> array_float{};
    std::vector<int> array_int{};
    
    if (all_is_number){
        array_int = read<int>(argument);
        std::vector<int> copy_array_int = array_int;
        MergeSort<int>(array_int);
        std::cout << "\nsorted array = ";
        print<int>(array_int, 0, array_int.size());
        std::cout << "\nstd::sort = ";
        std::sort(std::begin(copy_array_int), std::end(copy_array_int));
        print<int>(copy_array_int, 0, copy_array_int.size());
    }
    else{
        array_string = read<std::string>(argument);
        std::vector<std::string> copy_array_string = array_string;
        MergeSort<std::string>(array_string);
        std::cout << "\nsorted array = ";
        print<std::string>(array_string, 0, array_string.size());
        std::cout << "\nstd::sort = ";
        std::sort(std::begin(copy_array_string), std::end(copy_array_string));
        print<std::string>(copy_array_string, 0, copy_array_string.size());
    }
    return 0;
}

bool check_argument(std::string& argument){
    auto iterator = argument.cbegin();
    while(iterator != argument.cend()){
        if(*iterator == '-'){
            iterator++;
        }
        if(!isdigit(*iterator)){
            return false;
        }
        while(isdigit(*iterator)){
            iterator++;
        }
        if((*iterator != ' ') && (iterator != argument.cend()) && (*iterator != '.')){
            return false;
        }
        while(*iterator == ' '){
            iterator++;
        }
    }
    return true;
}