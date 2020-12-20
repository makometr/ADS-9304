#include "HeapSort.h"
#include "Data.h"

HeapSort::HeapSort(Data& data, SortMode mode)
{
    this->mode_ = mode;

    if (mode_ == SortMode::MaxHeap) {
        std::cout << "\nMaking Max-Heap...";
        for (int i = (data.array_.size() / 2 - 1); i >= 0; i--) {
            CreateMaxHeap(data.array_, data.array_.size(), i);
            data.PrintData(data.array_);
            std::cout << std::endl;
        }

        std::cout << "\n\nStart extraction of elements from the heap...";
        for (int i = (data.array_.size() - 1); i >= 0; i--)
        {
            std::cout << "\n\nSwap first and last elements - " << data.array_[0] << ' ' << data.array_[i] << '\n';
            std::swap(data.array_[0], data.array_[i]);

            std::cout << "Making Max-Heap from a reduced array...\n";
            CreateMaxHeap(data.array_, i, 0);

            data.PrintData(data.array_);
        }
    }
    else if (mode_ == SortMode::MinHeap) {
        std::cout << "\nMaking Min-Heap...";
        for (int i = (data.array_.size() / 2 - 1); i >= 0; i--) {
            CreateMinHeap(data.array_, data.array_.size(), i);
            data.PrintData(data.array_);
            std::cout << std::endl;
        }

        std::cout << "\n\nStart extraction of elements from the heap...";
        for (int i = (data.array_.size() - 1); i >= 0; i--)
        {
            std::cout << "\n\nSwap first and last elements - " << data.array_[0] << ' ' << data.array_[i] << '\n';
            std::swap(data.array_[0], data.array_[i]);

            std::cout << "Making Min-Heap from a reduced array...\n";
            CreateMinHeap(data.array_, i, 0);

            data.PrintData(data.array_);
        }
    }
}

HeapSort::~HeapSort()
{
    
}

void HeapSort::CreateMaxHeap(std::vector<int>& data, int heap_size, int root)
{
    int largest = root;
    int left = 2 * root + 1; // левый = 2*i + 1
    int right = 2 * root + 2; // правый = 2*i + 2

    if (left < heap_size && data[left] > data[largest]) {
        largest = left;
    }

    if (right < heap_size && data[right] > data[largest]) {
        largest = right;
    }

    if (largest != root)
    {
        std::swap(data[root], data[largest]);

        CreateMaxHeap(data, heap_size, largest);
    }
}

void HeapSort::CreateMinHeap(std::vector<int>& data, int heap_size, int root)
{
    int smallest = root;
    int left = 2 * root + 1; // левый = 2*i + 1
    int right = 2 * root + 2; // правый = 2*i + 2

    if (left < heap_size && data[left] < data[smallest]) {
        smallest = left;
    }

    if (right < heap_size && data[right] < data[smallest]) {
        smallest = right;
    }
       
    if (smallest != root)
    {
        std::swap(data[root], data[smallest]);

        CreateMinHeap(data, heap_size, smallest);
    }
}
