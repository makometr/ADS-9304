#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

template<typename T>
void printer(std::vector<T>& vec){
    for(int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
}

template<typename T>
T findMin(std::vector<T>& vec){
    T num = vec[0];
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] < num){
            num = vec[i];
        }
    }
    return num;
}

template<typename T>
T findMax(std::vector<T>& vec){
    T num = vec[0];
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] > num){
            num = vec[i];
        }
    }
    return num;
}

template<typename T>
void insertSort(std::vector<T>& vec){
    T x;
    int i, j;
    for(i = 0; i < vec.size(); i++) {
        x = vec[i];
        for (j = i - 1; j >= 0 && vec[j] > x; j--) {
            vec[j + 1] = vec[j];
        }
        vec[j+1] = x;
    }
}

template<typename T>
void solomonSort(std::vector<T>& vec){
    T min, max;
    T n = vec.size();
    min = findMin(vec);
    max = findMax(vec);
    T d = ((int)max - (int)min)/n;
    std::vector<std::vector<T>> newVec;
    newVec.resize((max - min)/d + 1);
    std::cout << "\nThrowing stones:\n\n";
    for(int i = 0; i < n; i++){
        int indx = ((int)vec[i] - (int)min)/d + 1;
        std::vector<T> tmp;
        tmp.push_back(vec[i]);
        if(!newVec[indx - 1].empty()){
            newVec[indx - 1].push_back(tmp[0]);
        }else {
            newVec[indx - 1] = tmp;
        }
        std::cout << "Added element " << vec[i] << " to heap with index " << indx - 1 << "\n";
        std::cout << "Heap with index " << indx - 1 << ": ";
        printer(newVec[indx - 1]);
    }
    vec.clear();
    std::cout << "\nPicking up stones:\n\n";
    for(int i = 0; i < newVec.size(); i++){
        if(!newVec[i].empty()){
            if(newVec[i].size() == 1){
                std::cout << "Picked heap with index " << i << " and pushed element to original vector." << "\n";
                std::cout << "Original vector is: ";
                vec.push_back(newVec[i][0]);
            }else if(newVec[i].size() == 2){
                std::cout << "Picked heap with index " << i << " and pushed two elements back to original vector." << "\n";
                std::cout << "Vector is: ";
                if(newVec[i][0] < newVec[i][1]){
                    vec.push_back(newVec[i][0]);
                    vec.push_back(newVec[i][1]);
                }else{
                    vec.push_back(newVec[i][1]);
                    vec.push_back(newVec[i][0]);
                }
            }else if(newVec[i].size() >= 3) {
                std::cout << "Picked heap with index " << i << " and pushed more than two elements to original vector." << "\n";
                std::cout << "Vector is: ";
                insertSort(newVec[i]);
                for(int j = 0; j < newVec[i].size(); j++){
                    vec.push_back(newVec[i][j]);
                }
            }
            printer(vec);
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2){
	std::cout << "Incorrect massive!\n";
	return 0;
    }
    std::string args(argv[1]);
    int flag = 1;//1 - int, 2 - char
    if(isalpha(args[0])){
        flag = 2;
    }
    if(isdigit(args[0])){
        flag = 1;
    }
    std::istringstream str(args);
    int elem1;
    char elem2;
    std::vector<int> v1;
    std::vector<char> v2;
    std::vector<int> spareV1;
    std::vector<char> spareV2;
    if(flag == 1){//for int
        while(str >> elem1){
            v1.push_back(elem1);
            spareV1.push_back(elem1);
        }
        std::cout << "\nSorting by Solomon:\n";
        int min = findMin(v1);
        int max = findMax(v1);
        if(max - min < v1.size()){
            std::cout << "Incorrect massive!\n";
            return 0;
        }
        solomonSort(v1);
        std::cout << "\nSorted vector:\n\n";
        printer(v1);
        std::cout << "\nSorted by std::sort:\n\n";
        std::sort(std::begin(spareV1), std::end(spareV1));
        printer(spareV1);
    }
    if(flag == 2){//for char
        while(str >> elem2){
            v2.push_back(elem2);
            spareV2.push_back(elem2);
        }
        std::cout << "\nSorting by Solomon:\n";
        char min = findMin(v2);
        char max = findMax(v2);
        if((int)max - (int)min < v2.size()){
            std::cout << "Incorrect massive!\n";
            return 0;
        }
        solomonSort(v2);
        std::cout << "\nSorted vector:\n\n";
        printer(v2);
        std::cout << "\nSorted by std::sort:\n\n";
        std::sort(std::begin(spareV2), std::end(spareV2));
        printer(spareV2);
    }
    return 0;
}


