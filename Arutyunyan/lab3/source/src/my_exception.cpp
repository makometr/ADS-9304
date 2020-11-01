#include "../lib/my_exception.h"

MyException::MyException(const ErrorCode code, const std::string&& str)
    : std::runtime_error(str), code_(code) {}

MyException::MyException(const MyException& err)
    : std::runtime_error(err.what()), code_(err.code_) {}

ErrorCode MyException::GetCode() { return code_; }

std::ostream& operator<<(std::ostream& out, const MyException object) {
  switch (object.code_) {
    case ErrorCode::kNone:
      out << "None";
      break;
    case ErrorCode::kIndexError:
      out << "IndexError: " << object.what();
      break;
    case ErrorCode::kValueError:
      out << "ValueError: " << object.what();
      break;
    case ErrorCode::kSyntaxError:
      out << "SyntaxError: " << object.what();
      break;
    case ErrorCode::kRuntimeError:
      out << "RuntimeError: " << object.what();
      break;
  }

  return out;
}