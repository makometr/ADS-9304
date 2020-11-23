#ifndef __ITERQSORT__H__
#define __ITERQSORT__H__

#include <iostream>
#include <stack>
#include <utility>

template <typename RandomIt>
void swapObjs(RandomIt left, RandomIt right)
{
    auto tmpSwap = *left;
    *left = *right;
    *right = tmpSwap;
}

template <typename RandomIt>
RandomIt partition(RandomIt left, RandomIt right)
{
    RandomIt pivotPosSelector = left;
    RandomIt pivot = right;

    for (auto it = left; it != pivot; ++it)
    {
        if (*it < *pivot)
        {
            if (it != pivotPosSelector)
                swapObjs<RandomIt>(it, pivotPosSelector);
            ++pivotPosSelector;
        }
    }
    // ставим pivot на свое место
    swapObjs<RandomIt>(pivot, pivotPosSelector);
    return pivotPosSelector;
}

template <typename RandomIt>
void iterQSort(RandomIt start, RandomIt end)
{
    if (start < end)
    {
        std::stack<std::pair<RandomIt, RandomIt>> stck;
        stck.push(std::make_pair<RandomIt, RandomIt>(std::move(start), std::move(end)));

        // счетчик шагов
        int counter = 0;

        // вывод на экран шага
        std::cout << "Step 0:\n";
        for (auto it = start; it != end; ++it)
            std::cout << *it << ' ';
        std::cout << '\n';

        while (!stck.empty())
        {
            ++counter;
            std::pair<RandomIt, RandomIt> borders = stck.top();
            stck.pop();

            RandomIt pivot = partition(borders.first, borders.second - 1);

            // вывод на экран шага
            std::cout << "Step " + std::to_string(counter) + ":\n";
            for (auto it = start; it != end; ++it)
                std::cout << *it << ' ';
            std::cout << '\n';

            // если оба отрезка длиннее 1-го элемента
            if ((pivot - 1 > borders.first) && (pivot + 1 < borders.second - 1))
            {
                // больший отрезок первым кладем на стек. Так мы в среднем уменьшим наибольшую высоту стека на один.
                if (((pivot - 1) - borders.first) > (borders.second - 1) - (pivot + 1))
                {
                    stck.push(std::make_pair<RandomIt, RandomIt>(std::move(std::get<0>(borders)), std::move(pivot)));
                    stck.push(std::make_pair<RandomIt, RandomIt>(pivot + 1, std::move(std::get<1>(borders))));
                }
                else
                {
                    stck.push(std::make_pair<RandomIt, RandomIt>(pivot + 1, std::move(std::get<1>(borders))));
                    stck.push(std::make_pair<RandomIt, RandomIt>(std::move(std::get<0>(borders)), std::move(pivot)));
                }
            }
            else
            {
                if (pivot - 1 > borders.first)
                    stck.push(std::make_pair<RandomIt, RandomIt>(std::move(std::get<0>(borders)), std::move(pivot)));
                if (pivot + 1 < borders.second - 1)
                    stck.push(std::make_pair<RandomIt, RandomIt>(pivot + 1, std::move(std::get<1>(borders))));
            }
        }
    }
}

#endif //!__ITERQSORT__H__