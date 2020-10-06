#include "../lib/logical_expression.h"

LogicalExpression::LogicalExpression(const std::string &expr)
    : error_(kNone), expr_(expr), index_(0) {
  DeleteSpaces(expr_);
}

bool LogicalExpression::Analyze() {
  try {
    CheckNextExpr();
    if (index_ != expr_.size()) {
      throw MyException(kSyntaxError, "invalid syntax");
    }
  } catch (MyException &err) {
    error_ = err;
    return false;
  }
  return true;
}

void LogicalExpression::CheckNextExpr() {
  if (IsAnd() || IsOr()) {
    CheckBool();
  } else if (IsNot()) {
    CheckBool(true);
  } else if (!(IsFalse() || IsTrue() || IsID())) {
    throw MyException(kSyntaxError, "invalid syntax");
  }
}

MyException LogicalExpression::GetError() { return error_; }

bool LogicalExpression::IsFalse() { return CompareStrings(kFalse); }

bool LogicalExpression::IsTrue() { return CompareStrings(kTrue); }

bool LogicalExpression::IsID() {
  char c = expr_[index_];
  bool result = 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
  if (result) ++index_;
  return result;
}

bool LogicalExpression::IsAnd() { return CompareStrings(kAnd); }

bool LogicalExpression::IsOr() { return CompareStrings(kOr); }

bool LogicalExpression::IsNot() { return CompareStrings(kNot); }

void LogicalExpression::CheckBool(bool is_not) {
  if (expr_[index_] != '(') {
    throw MyException(kSyntaxError, "missing \"(\"");
  }

  ++index_;
  CheckNextExpr();

  if (!is_not) {
    if (expr_[index_] != ',') {
      throw MyException(kSyntaxError, "missing \",\"");
    }
    ++index_;
    CheckNextExpr();
  }

  if (expr_[index_] != ')') {
    throw MyException(kSyntaxError, "missing \")\"");
  }
  ++index_;
}

void LogicalExpression::DeleteSpaces(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char sym) { return std::isspace(sym); }),
            str.end());
}

bool LogicalExpression::CompareStrings(NamesType type) {
  bool result = !expr_.compare(index_, names_[type].size(), names_[type]);
  if (result) {
    index_ += names_[type].size();
  }
  return result;
}
