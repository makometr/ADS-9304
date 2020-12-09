#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>


int main(){

    std::string inputString {};

    getline(std::cin, inputString);

    std::stringstream ss(inputString);

    std::vector<int> arr {};

    std::copy(std::istream_iterator<int>(ss), {}, back_inserter(arr));

    size_t position = 0;

    for(size_t i = 0; i < arr.size(); i++){
        position = i * 2 + 1;
        if(arr[i] < arr[position] && position < arr.size()){
            std::cout << arr[i] << '[' << i << ']' << " < " << arr[position] << '[' << position << ']' << '\n';
            std::cout << "It's not a weak heap!" << std::endl;
            break;
        }
        if(i == arr.size() - 1){
            std::cout << "It's a weak heap!" << std::endl;
            return 0;
        }
    }

    std::vector<bool> BIN {};
    size_t binSize;
    if(arr.size() % 2){
        binSize = arr.size() / 2;
    }else{
        binSize = (arr.size() / 2) - 1;
    }
    BIN.resize(binSize + 1);

    size_t digit;

    for(int i = arr.size() - 1; i >= 0; i--){

        digit = i;

        while(digit){   
            if((digit) % 2){
                digit = digit / 2;
                break;
            }else{
                digit = digit / 2;
            }
        }

        if(arr[i] > arr[digit]){
            if(i < BIN.size()){
                BIN[i] = !BIN[i];
            }
            std::swap(arr[i], arr[digit]);
        }
    }

    for(const auto &x : arr){
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    for(size_t i = 1; i < BIN.size(); i++){
        std::cout << BIN[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
} 