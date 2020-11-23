#include<iostream>
#include<algorithm>
#include<memory>

int main(){
    size_t count;
    std::cin >> count;
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(count);
    for(int i = 0; i < count; i++)
        std::cin >> arr[i];
    size_t k;
    std::cin >> k;
    std::sort(arr.get(), arr.get()+count);
    std::cout <<  "Sorted array: ";
    for(int i = 0; i < count; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
    std::cout << "K min = " << arr[k-1] << "\n";
    return 0;
}
