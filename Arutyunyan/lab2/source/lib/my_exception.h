#ifndef MY_EXCEPTION_H_
#define MY_EXCEPTION_H_

#include <iostream>

enum class ErrorCode {
  kNone = 0,
  kIndexError,
  kValueError,
  kSyntaxError,
  kRuntimeError
};

class MyException {
 public:
  MyException(const ErrorCode code, const std::string&& str = "");
  MyException(const MyException& err);
  ErrorCode GetCode();
  friend std::ostream& operator<<(std::ostream& out, const MyException object);
  ~MyException() = default;

 private:
  ErrorCode code_;
  std::string str_;
};

#endif  // MY_EXCEPTION_H_