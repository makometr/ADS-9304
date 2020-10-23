#include "../lib/algebraic_expression.h"

AlgebraicExpression::AlgebraicExpression(std::string_view expr)
    : expr_(expr), err_(ErrorCode::kNone) {}

MyException AlgebraicExpression::GetError() { return err_; }

bool AlgebraicExpression::Analyze() {
  try {
    HierarchicalList list_expr(expr_);
    CheckCorrect(list_expr);
  } catch (const MyException& err) {
    err_ = err;
    return false;
  }
  return true;
}

bool AlgebraicExpression::CheckCorrect(const HierarchicalList& object) {
  Node curr = object.GetHead();

  // one argument - Hierarchical List
  if (curr.IsHierarchicalList()) {
    CheckCorrect(curr.GetHierarchicalList());

    // one operation - sqrt
  } else if (curr.IsOperation() && curr.GetOperation() == TypeOfObject::kSqrt) {
    if (curr.GetNext() == nullptr || curr.GetNext()->IsOperation()) {
      throw MyException(ErrorCode::kSyntaxError,
                        "not enough arguments or invalid syntax");
    } else {
      // next item is a hierarchical list
      if (curr.GetNext()->IsHierarchicalList()) {
        CheckCorrect(curr.GetNext()->GetHierarchicalList());
      }
      // shift by 1 elements
      curr = *(curr.GetNext());
    }
    // any operation
  } else if (curr.IsOperation()) {
    if (curr.GetNext() == nullptr || curr.GetNext()->GetNext() == nullptr) {
      throw MyException(ErrorCode::kSyntaxError, "not enough arguments");
    }

    Node next = *(curr.GetNext());
    Node next_x2 = *(next.GetNext());

    if (next.IsOperation() || next_x2.IsOperation()) {
      throw MyException(ErrorCode::kSyntaxError, "invalid argument");
    }

    // log(number_1, number_2)
    if (curr.GetOperation() == TypeOfObject::kLog &&
        ((next.IsNumber() &&
          (next.GetNumber() <= 0 || next.GetNumber() == 1)) ||
         (next_x2.IsNumber() && next_x2.GetNumber() <= 0))) {
      throw MyException(ErrorCode::kValueError,
                        "invalid argument of the logarithm");
    } else {
      // next item is a hierarchical list
      if (next.IsHierarchicalList()) {
        CheckCorrect(next.GetHierarchicalList());
      }
      // next_x2 item is a hierarchical list
      if (next_x2.IsHierarchicalList()) {
        CheckCorrect(next_x2.GetHierarchicalList());
      }
      // shift by 2 elements
      curr = next_x2;
    }
  }

  if (curr.GetNext() != nullptr) {
    throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
  }

  return true;
}
