#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void print(std::vector<T>& vector){
    std::cout<<"[ ";
    for (auto i : vector) {
        std::cout<<i<<" ";
    }
    std::cout<<"]";
    std::cout<<"\n";
}

template <typename T>
void oddEvenSort(std::vector<T>& vector){

    std::cout<<"oddEvenSort is running... \n";
    std::cout<<"\tOriginal array: ";
    print(vector);

    for (size_t i = 0; i < vector.size(); i++){
        for (size_t j = (i % 2) ? 0 : 1; j + 1 < vector.size(); j += 2){        // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное

            std::cout<<"\n\tCurrent array: ";
            print(vector);

            std::cout<<"\tCompare "<<vector[j]<<" and "<<vector[j+1]<<"\n";
            if (vector[j] > vector[j + 1]) {
                std::cout<<"\tSwapping "<<vector[j]<<" and "<<vector[j+1]<<"\n";
                std::swap(vector[j], vector[j + 1]);
            }
        }
    }
}

template <typename T>
void bubbleSort(std::vector<T>& vector){

    std::cout<<"bubbleSort is running... \n";
    std::cout<<"\tOriginal array: ";
    print(vector);

    bool swapped;
    for (int i = 0; i < vector.size()-1; i++){
        swapped = false;
        for (int j = 0; j < vector.size()-i-1; j++){

            std::cout<<"\n\tCurrent array: ";
            print(vector);

            std::cout<<"\tCompare "<<vector[j]<<" and "<<vector[j+1]<<"\n";
            if (vector[j] > vector[j+1]){
                std::cout<<"\tSwapping "<<vector[j]<<" and "<<vector[j+1]<<"\n";
                std::swap(vector[j], vector[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {          // Если в процессе прохода не было ни одной замены, то выход из функции
            break;
        }
    }
}

template <typename T>
bool isEqual(std::vector<T> vector1, std::vector<T> vector2){
    return std::equal(vector1.begin(), vector1.end(), vector2.begin());
}

bool isCorrect(const std::string& str){

    if (str.empty()){
        return false;
    }
    for(char i:str){
        if (!isdigit(i) && i != ' ' && i != '-'){
            return false;
        }
    }
    return true;
}

void get_numbers(std::vector<int> & result, const std::string & str) {
    bool found = false;
    int number = 0;
    bool negative = false;

    for (char ch : str) {
        if (ch >= '0' && ch <= '9' || ch == '-') {
            if (ch =='-'){
                negative= true;
                continue;
            }
            const int digit = ch - '0';
            number = number*10 + digit;
            found = true;
        }
        else {
            if (found) {
                if(negative){
                    number=number*(-1);
                    negative= false;
                }
                result.push_back(number);

                number = 0;
                found = false;
            }
        }
    }

    if (found) {
        if(negative){
            number=number*(-1);
        }
        result.push_back(number);
    }
}

int main(){

    std::string str;
    getline(std::cin, str);
    if(!isCorrect(str)){
        std::cout<<"Error: incorrect value";
        return EXIT_FAILURE;
    }
    std::vector<int> vector;

    get_numbers(vector,str);
    std::vector<int> vector1 = vector;
    std::vector<int> vector2 = vector;

    oddEvenSort(vector1);
    std::cout<<"RESULT OF oddEvenSort:\t";
    print(vector1);
    std::cout<<"\n";

    bubbleSort(vector2);
    std::cout<<"RESULT OF bubbleSort:\t";
    print(vector2);
    std::cout<<"\n";

    std::sort(vector.begin(), vector.end());
    std::cout<<"RESULT OF std::sort: \t";
    print(vector);
    std::cout<<"\n";

    if (isEqual(vector,vector1)){
        std::cout<<"The results of sorting with std:: sort and oddEvenSort are the SAME\n";
    } else std::cout<<"The results of sorting with std:: sort and oddEvenSort are DIFFERENT\n";

    if (isEqual(vector,vector2)){
        std::cout<<"The results of sorting with std:: sort and bubbleSort are the SAME\n";
    } else std::cout<<"The results of sorting with std:: sort and bubbleSort are DIFFERENT\n";

    return 0;
}
