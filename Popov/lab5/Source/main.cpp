#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>   



std::vector<unsigned> leonardo_numbers(const unsigned sizeVec){
    std::vector<unsigned> leonardo {};
    unsigned a = 1;
    unsigned b = 1;
    unsigned c = 1;
    while(b <= sizeVec){
        leonardo.emplace_back(b);
        a = b;
        b = c;
        c = a + b + 1;
    }
    return leonardo;
}



int main(){

    std::string inputString {};
    getline(std::cin, inputString);

    std::stringstream strStream(inputString);
    std::vector<int> vec {};

    std::copy(std::istream_iterator<int>(strStream), {}, back_inserter(vec));
    
    std::vector<unsigned> leonardo = leonardo_numbers(vec.size());

    unsigned arrSize = vec.size();
    unsigned count = 0;

    std::cout << "Размер массива - " << arrSize << '\n';

    auto PR = [&arrSize, &leonardo, &count, &vec](unsigned iter, auto &&PR){

        ++count;

        if(arrSize == 0){
            return;
        }

        for(size_t i = leonardo.size() - 1; i >= 0; i--){
            if(arrSize >= leonardo[i]){
                arrSize -= leonardo[i];
                std::cout << "Куча " << count << " [" << leonardo[i] << "]: ";
                for(size_t j = 0; j < leonardo[i]; j++){
                    std::cout << vec[j + iter] << ' ';
                }
                std::cout << std::endl;
                PR(leonardo[i], PR);
                break;
            }
        }

    };
    
    PR(0, PR);

    return 0;
}