#include<iostream>
#include<memory>

#define PRINT
#ifdef PRINT
#define NORMAL "\x1b[0m"
#define ORIGIN "\x1b[34m"
#define SORTED "\x1b[35m"
#define SEPARETED "\x1b[33m"
#define FIND "\x1b[1;31m"
#define DEEP(x) (x*(std::string("|   ")))

std::string operator*(int x, std::string str){
    if(!x) return std::string();
    std::string res = str;
    for(int i = 1; i < x; i++)
        res += str;
    return res;
}

#endif

template<typename T>
T find_k_min(T* start, T* end, size_t k){
    if (k > end-start) throw std::logic_error("K > size");
    size_t len = end - start;
    int deep = -1;
    auto quicksort = [](T* start, T* end, auto&& quicksort)->void{
        if(start >= end) return;
        size_t left = 0, right = end - start, len = right+1;
        T pivot = start[len/2];
        while(left <= right){
            while((left +1) < len && start[left] < pivot) left++;
            while(right > 0 && start[right] > pivot) right--;
            if(left < right){
                T temp = start[left];
                start[left] = start[right];
                start[right] = temp;
                if(right) right--;
                if((left + 1) < len) left++;
            }else break;
        }
        quicksort(start, start+left-1, quicksort);
        quicksort(start+left, end, quicksort);
    };

    auto pick_pivot = [&deep, &quicksort](T* start, T* end, auto&& quickselect)->T{
        #ifdef PRINT
        deep++;
        std::cout << NORMAL << DEEP(deep) <<  "Pick Pivot\n";
        #endif
        if( (end - start) < 6){
            quicksort(start, end, quicksort);
            #ifdef PRINT
            std::cout << NORMAL << DEEP(deep) << SORTED << "Sorted array: [ ";
            for(int i = 0; start + i <= end; i++)
                std::cout<< start[i] << " ";
            std::cout << "]\n" << NORMAL<< DEEP(deep) << FIND << " Pivot = " << start[(end-start+1)/2] << "\n"; 
            std::cout << NORMAL << DEEP(deep) << "End Pick Pivot\n";
            deep--;
            #endif
            return start[(end-start+1)/2];
        }
        size_t len = (end - start);
        std::unique_ptr<T[]> medians = std::make_unique<T[]>((len%5 == 0 ? len/5 : (len/5 + 1)));
        len = len/5;
        #ifdef PRINT
        std::cout << NORMAL << DEEP(deep) << SORTED << "Sorted groups of 5:";
        #endif
        for(int i = 0; i < len; i++){
            quicksort(start + i * 5, start + (i + 1) * 5 - 1, quicksort);
            medians[i] = start[i * 5 + 2];
            #ifdef PRINT
            std::cout << " [ ";
            for(int j = 0; j < 5; j++)
                std::cout << start[i * 5 + j] << " ";
            std::cout << "]";
            #endif
        }
        if( (len * 5) < (end - start)){
            quicksort(start + len * 5, end, quicksort);
            medians[len] = start[(end - start - len * 5)/2 + len * 5];
            len++;
            #ifdef PRINT
            std::cout << " [ ";
            for(int j = 0; j <= (end - start - (len - 1) * 5); j++)
                std::cout << start[(len - 1) * 5 + j] << " ";
            std::cout << "]";
            #endif
        }
        #ifdef PRINT
        std::cout << "\n" << NORMAL << DEEP(deep) << ORIGIN << "Medians: [ ";
        for(int i = 0; i < len; i++)
            std::cout << medians[i] << " ";
        std::cout << "]\n";
        T ret = quickselect(medians.get(), medians.get()+len-1, len/2, quickselect);
        std::cout << NORMAL << DEEP(deep) << "End Pick Pivot\n";
        deep--;
        return ret;
        #else
        return quickselect(medians.get(), medians.get()+len-1, len/2, quickselect);
        #endif
    };

    auto quickselect = [&deep, &quicksort, &pick_pivot](T* start, T* end, size_t k, auto&& quickselect)->T{
        #ifdef PRINT
        deep++;
        std::cout << NORMAL << DEEP(deep) << "QuickSelect\n" << NORMAL << DEEP(deep) << FIND << "Finding element on " << k+1 << " position\n"<< NORMAL << DEEP(deep) << ORIGIN << "Origin array: ";
        for(int i = 0; start + i <= end; i++)
            std::cout << start[i] << " ";
        std::cout<< "\n";
        #endif
        if((end - start) < 6){
            quicksort(start, end, quicksort);
            #ifdef PRINT
            std::cout << NORMAL << DEEP(deep) << SORTED << "Sorted array: ";
            for(int i = 0; start + i <= end; i++)
                std::cout << start[i] << " ";
            std::cout<< "\n";
            std::cout << NORMAL << DEEP(deep) << FIND << "Find: " << start[k] << "\n" << NORMAL << DEEP(deep) << "End Quick Select\n";
            deep--;
            #endif
            return start[k];
        }
        T pivot = pick_pivot(start, end, quickselect);
        #ifdef PRINT
        std::cout << NORMAL << DEEP(deep) << ORIGIN << "Pivot: " << pivot << "\n";
        #endif
        cycle:
        size_t left = 0, right = end - start, len = right+1;
        while(left < right){
            while((left +1)  < len && start[left] < pivot) left++;
            while(right > 0 && start[right] >= pivot) right--;
            if(left <= right){
                T temp = start[left];
                start[left] = start[right];
                start[right] = temp;
                if(right) right--;
                if(left + 1 < len) left++;
            }
        }
        while(left > 0 && start[left] > pivot) left--;
        if(left == 0 && start[left] > pivot){
            pivot = start[left];
            goto cycle;
        }
        #ifdef PRINT
        std::cout << NORMAL << DEEP(deep) << SEPARETED << "Separeted array: Left: [ ";
        for(int i = 0; i <= left; i++)
            std::cout << start[i] << " ";
        std::cout << "] Right: [ ";
        for(int i = left+1; i < len; i++)
            std::cout << start[i] << " ";
        std::cout<< "]\n";
        T res = (left >= k ? quickselect(start, start+left, k, quickselect) : quickselect(start+left+1, end, k-left-1, quickselect));
        std::cout << NORMAL << DEEP(deep) << "End QuickSelect\n";
        deep--;
        return res;
        #else
        return (left >= k ? quickselect(start, start+left, k, quickselect) : quickselect(start+left+1, end, k-left-1, quickselect));
        #endif
    };
    

    return quickselect(start, end, k, quickselect);
}

int main(){
    size_t count;
    std::cin >> count;
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(count);
    for(int i = 0; i < count; i++)
        std::cin >> arr[i];
    size_t k;
    std::cin >> k;
    try{
        int res = find_k_min(arr.get(), arr.get()+count-1, k-1); 
        std::cout << "K min = " << res << "\n";
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
