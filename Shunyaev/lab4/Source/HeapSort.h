#pragma once
#include <vector>
#include <iostream>

class Data;

enum class SortMode {
	MaxHeap,
	MinHeap,
};

class HeapSort
{
public:
	SortMode mode_;

	HeapSort(Data& data, SortMode mode);
	~HeapSort();

	void CreateMaxHeap(std::vector<int>& data, int heap_size, int root);
	void CreateMinHeap(std::vector<int>& data, int heap_size, int root);
};

