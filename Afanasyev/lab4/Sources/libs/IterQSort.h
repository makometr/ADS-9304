#ifndef __ITERQSORT__H__
#define __ITERQSORT__H__

#include <stack>
#include <iostream>

template <typename RandomIt>
void swapForSort(RandomIt left, RandomIt right)
{
    auto tmpSwap = *left;
    *left = *right;
    *right = tmpSwap;
}

template <typename RandomIt>
void iterQSort(RandomIt start, RandomIt end)
{
    if (start < end)
    {

        std::stack<RandomIt> stck;
        stck.push(end);
        stck.push(start);

        int counter = 0;

        std::cout << "Step " + std::to_string(counter) + ":\n";
        for (auto it = start; it != end; ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
        while (!stck.empty())
        {
            ++counter;
            RandomIt newStart = stck.top();
            stck.pop();

            RandomIt newEnd = stck.top();
            stck.pop();

            RandomIt iterToCompareWithPivot = newStart;
            RandomIt pivot = newEnd - 1;

            for (auto it = newStart; it != newEnd; ++it)
            {
                if (*it < *pivot)
                {
                    swapForSort<RandomIt>(it, iterToCompareWithPivot);
                    ++iterToCompareWithPivot;
                }
            }
            swapForSort<RandomIt>(pivot, iterToCompareWithPivot);
            std::cout << "Step " + std::to_string(counter) + ":\n";
            for (auto it = start; it != end; ++it)
                std::cout << *it << ' ';
            std::cout << '\n';

            if (iterToCompareWithPivot - 1 > newStart)
            {
                stck.push(iterToCompareWithPivot);
                stck.push(newStart);
            }
            if (iterToCompareWithPivot + 1 < newEnd)
            {
                stck.push(newEnd);
                stck.push(iterToCompareWithPivot + 1);
            }
        }
    }
}

#endif //!__ITERQSORT__H__