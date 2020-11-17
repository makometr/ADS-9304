#include <iostream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <cstdlib>

template <typename T>
void comb_sort(std::vector<T> &data){
    double factor = 1.2473309;
    int step = data.size() - 1;
    int permutation_counter = 0;
    std::vector<T> check_vect = data;
    std::sort(check_vect.begin(), check_vect.end());


    while (step >= 1){
        std::cout << "distance between elements: " << (int)step << '\n';
        for (int i = 0; i + step < data.size(); i++){
            if (data[i] > data[i + step]){
                permutation_counter++;
                std::cout << permutation_counter << " permutation\n";
                std::cout << "the unmodified vector: ";
                for (int j = 0; j < data.size(); j++){
                    if (j == i){
                        std::cout << "\033[1;31m" << data[j]  << " \033[0m";
                    } else if (j == i + step){
                        std::cout << "\033[1;34m" << data[j]  << " \033[0m";
                    } else {
                        std::cout << data[j] << " ";
                    }
                }
                std::cout << '\n';
                std::swap(data[i], data[i + step]);
                std::cout << "the modified vector: ";
                for (int k = 0; k < data.size(); k++){
                    if (k == i){
                        std::cout << "\033[1;34m" << data[k]  << " \033[0m";
                    } else if (k == i + step){
                        std::cout << "\033[1;31m" << data[k]  << " \033[0m";
                    } else {
                        std::cout << data[k] << " ";
                    }
                }
                std::cout << '\n';
            }
        }
        std::cout << "\n\n";
        step /= factor;
    }
    if (data == check_vect){
        std::cout << "sorting spent " << permutation_counter << " permutations\n";
    } else {
        std::cout << "sorting failed";
    }
}

template <typename T>
std::vector<T> create_rand_vect(int size){
    std::vector<T> vect;
    srand(time(0));
    if (sizeof(T) == sizeof(int)){
        for (int i = 0; i < size; i++){
            vect.push_back(rand() % 5000);
        }
    } else if (sizeof(T) == sizeof(char)){
        for (int i = 0; i < size; i++){
            vect.push_back((char)(rand() % 95 + 32));
        }
    } else if (sizeof(T) == sizeof(double)){
        for (int i = 0; i < size; i++){
            vect.push_back((rand() % 5000) * 0.1);
        }
    }
    return vect;
}

bool string_to_int(char* str){
    char* endptr;
    strtol(str, &endptr, 10);
    if (*endptr) {
        return false;
    } else {
        return true;
    }
}

void key(int argc, char** argv, int size){
    int opt;
    const char *opts = "cdi";
    struct option long_opts[] = {
            {"char", no_argument, NULL, 'c'},
            {"double", no_argument, NULL, 'd'},
            {"int", no_argument, NULL, 'i'},
            {0, 0, 0, 0}
    };
    int long_index;
    opt = getopt_long(argc, argv, opts, long_opts, &long_index);
    if (opt == 'c'){
        std::vector<char> arr = create_rand_vect<char>(size);
        comb_sort(arr);
    } else if (opt == 'i'){
        std::vector<int> arr = create_rand_vect<int>(size);
        comb_sort(arr);
    } else if (opt == 'd'){
        std::vector<double> arr = create_rand_vect<double>(size);
        comb_sort(arr);
    } else {
        std::cout << "no such key";
    }
};

int main(int argc, char** argv){
    int size = 0;
    char *endptr;
    if (argc == 3){
        if (string_to_int(argv[1])){
            size = strtol(argv[1], &endptr, 10);
            key(argc, argv, size);
        } else if (string_to_int(argv[2])){
            size = strtol(argv[2], &endptr, 10);
            key(argc, argv, size);
        } else {
            std::cout << "you did not specify the size of the vector\n";
        }
    } else {
        std::cout << "you specified an invalid number of arguments\n";
    }

    return 0;

}
