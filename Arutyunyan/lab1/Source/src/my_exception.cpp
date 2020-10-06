#include "../lib/my_exception.h"

MyException::MyException(const ErrorCode code, const std::string&& str)
    : code_(code), str_(str) {}

ErrorCode MyException::GetCode() { return code_; }

std::ostream& operator<<(std::ostream& out, const MyException&& object) {
  switch (object.code_) {
    case ErrorCode::kNone:
      out << "None";
      break;
    case ErrorCode::kIndexError:
      out << "IndexError: " << object.str_;
      break;
    case ErrorCode::kValueError:
      out << "ValueError: " << object.str_;
      break;
    case ErrorCode::kSyntaxError:
      out << "SyntaxError: " << object.str_;
      break;
    case ErrorCode::kRuntimeError:
      out << "RuntimeError: " << object.str_;
      break;
  }

  return out;
}