#ifndef HIERARCHICAL_LIST_H_
#define HIERARCHICAL_LIST_H_

#include <algorithm>
#include <iostream>
#include <string>

#include "my_exception.h"
#include "node.h"

enum class NamesType { kLog = 0, kSqrt };

class HierarchicalList {
 public:
  HierarchicalList();
  HierarchicalList(std::string_view str);

  const Node& GetHead() const;

  ~HierarchicalList() = default;

 private:
  static const std::string names_[2];
  std::shared_ptr<Node> head_;
  std::shared_ptr<Node> end_;

  void AppendArgumentOfLogOrSqrt(std::string_view str, int begin, int end,
                                 char sym,
                                 std::shared_ptr<HierarchicalList>& h_list);

  template <typename T>
  void Append(T object);

  int GetDistanceToClosingBracket(std::string_view str);
  int GetFirstNonSpace(std::string_view str, int pos);
  int GetDistanceToComma(std::string_view str);

  bool CompareStrings(std::string_view str, NamesType type);
  int IsVariable(std::string_view str);
  int IsNumber(std::string_view str);
  bool IsSqrt(std::string_view str);
  bool IsLog(std::string_view str);
};

#endif  // HIERARCHICAL_LIST_H_
