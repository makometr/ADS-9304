#ifndef ALGEBRAIC_EXPRESSION_H_
#define ALGEBRAIC_EXPRESSION_H_

#include <string>

#include "my_exception.h"
#include "hierarchical_list.h"

class AlgebraicExpression {
 public:
  AlgebraicExpression(std::string_view expr);
  MyException GetError();
  bool Analyze();
  bool CheckCorrect(const HierarchicalList& object);
  ~AlgebraicExpression() = default;

 private:
  std::string expr_;
  MyException err_;
};

#endif  // ALGEBRAIC_EXPRESSION_H_