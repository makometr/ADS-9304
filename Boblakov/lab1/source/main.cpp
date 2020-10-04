#include <iostream>
#include "recSearch.h"


int main() {
    unsigned int from, to,n,i,j;
    std::cout<<"N = ";
    std::cin>>n;
    std::cout<<"from to\n";
    std::cin>>from>>to;
    from--;
    to--;
    std::cout<<"enter pairs\n";
    int** arr=new int*[n];
    for (int k = 0; k < n; ++k) {
        arr[k]=new int[n];
    }
    for (int k = 0; k < n; ++k) {
        for (int l = 0; l < n; ++l) {
            arr[k][l]=0;
        }
    }
    do {
        std::cin>>i;
        std::cin>>j;
        if(i>n || j>n ||((i>=j))&& (i!=0)){
            std::cout<<"Error: incorrect value\n";
            return EXIT_FAILURE;
        }
        if(i==0 ||j==0){
            break;
        }
        arr[i-1][j-1]=1;
        arr[j-1][i-1]=1;
    }while(i!=0 || j!=0);

    bool* watched = new bool[n];
    for (int k = 0; k < n; ++k) {
        watched[k]=false;
    }
    bool isTrue=recSearch(from,to,n,arr,watched);
    if (isTrue){
        std::cout<<"true";
    }    else std::cout<<"false";

    for (int k = 0; k < n; ++k) {
        delete arr[k];
    }
    delete[] arr;
    delete[] watched;
    return 0;
}

