#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <iostream>
#include <memory>
#include <vector>

template <typename RandomIt>
void PrintStep(RandomIt first, RandomIt last, size_t step_quantity,
               size_t width) {
  std::cout << "Step №" << step_quantity << ":\n    (";
  for (size_t i = 0; first != last; ++first, ++i) {
    if (i && !(i % width)) {
      std::cout << ") ";
    }
    if (i && !(i % width)) {
      std::cout << '(';
    }
    std::cout << *first;
    if (((i + 1) % width) && !(first + 1 == last)) {
      std::cout << ' ';
    }
  }
  std::cout << ")\n";
}

template <typename RandomIt>
void Copy(RandomIt additional, RandomIt main, size_t len) {
  for (size_t i = 0; i < len; ++i, ++additional, ++main) {
    *main = *additional;
  }
}

template <typename RandomIt>
void Merge(RandomIt first, RandomIt second, RandomIt end, RandomIt first_add) {
  RandomIt curr_first = first;
  RandomIt curr_second = second;
  RandomIt curr_add = first_add;
  for (size_t i = 0, len = end - first; i < len; ++i, ++curr_add) {
    if (curr_first != second &&
        (curr_second == end || !(*curr_second < *curr_first))) {
      *curr_add = *curr_first;
      ++curr_first;
    } else {
      *curr_add = *curr_second;
      ++curr_second;
    }
  }
}

template <typename RandomIt, typename RandomType>
void MergeSort(RandomIt first, RandomIt last) {
  size_t len = last - first;
  if (last - first < 2) {
    return;
  }
  std::vector<RandomType> additional;
  additional.resize(len);

  size_t step_quantity = 1;
  for (size_t width = 1; width < len; width *= 2) {
    PrintStep<RandomIt>(first, last, step_quantity++, width);
    for (size_t i = 0; i < len; i += 2 * width) {
      Merge<RandomIt>(first + i, first + std::min(i + width, len),
                      first + std::min(i + 2 * width, len),
                      additional.begin() + i);
    }
    Copy<RandomIt>(additional.begin(), first, len);
  }
}

#endif  // MERGE_SORT_H_