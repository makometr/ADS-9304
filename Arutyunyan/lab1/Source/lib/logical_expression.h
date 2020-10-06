#ifndef LOGICAL_EXPRESSION_H_
#define LOGICAL_EXPRESSION_H_

#include <algorithm>
#include <iostream>
#include <string>

#include "my_exception.h"

enum class NamesType { kFalse = 0, kTrue, kAnd, kOr, kNot };

class LogicalExpression {
 public:
  LogicalExpression(const std::string& expr);
  bool Analyze();
  MyException GetError();
  ~LogicalExpression() = default;

 private:
  const std::string names_[5] = {"FALSE", "TRUE", "AND", "OR", "NOT"};
  MyException error_;
  std::string expr_;
  int index_;

  void DeleteSpaces(std::string& str);
  bool CompareStrings(NamesType type);
  bool IsFalse();
  bool IsTrue();
  bool IsID();
  bool IsAnd();
  bool IsOr();
  bool IsNot();
  void CheckBool(bool is_not = false);
  void CheckNextExpr();
};

#endif  // LOGICAL_EXPRESSION_H_