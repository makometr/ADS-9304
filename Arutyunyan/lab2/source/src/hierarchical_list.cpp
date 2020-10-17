#include "../lib/hierarchical_list.h"

const std::string HierarchicalList::names_[] = {"log", "sqrt"};

HierarchicalList::HierarchicalList() : head_(nullptr), end_(nullptr) {}

HierarchicalList::HierarchicalList(std::string_view str)
    : head_(nullptr), end_(nullptr) {
  int curr_index = GetFirstNonSpace(str, 0);
  bool first_iteration = true;
  int count_of_brackets = 0;
  int shift = 1;

  if (curr_index == str.size()) {
    throw MyException(ErrorCode::kSyntaxError, "empty string");
  }

  while (curr_index != str.size()) {
    unsigned char curr_sym = str[curr_index];

    if (curr_sym == '(' && first_iteration) {
      ++count_of_brackets;

    } else if (curr_sym == '(') {
      int distance_to_closing_bracket =
          GetDistanceToClosingBracket(str.substr(curr_index, str.size()));
      std::string_view temp =
          str.substr(curr_index, 1 + distance_to_closing_bracket);
      std::shared_ptr<HierarchicalList> h_list(new HierarchicalList(temp));
      Append(h_list);
      shift = 1 + distance_to_closing_bracket;

    } else if (curr_sym == ')') {
      --count_of_brackets;

    } else if (curr_sym == '+') {
      Append(TypeOfObject::kPlus);

    } else if (curr_sym == '-' && !(curr_index + 1 != str.size() &&
                                    isdigit(str[curr_index + 1]))) {
      Append(TypeOfObject::kMinus);

    } else if (curr_sym == '*') {
      Append(TypeOfObject::kMultiply);

    } else if (IsLog(str.substr(curr_index, str.size()))) {
      std::shared_ptr<HierarchicalList> h_list(new HierarchicalList());
      h_list->Append(TypeOfObject::kLog);  // adding the operation

      curr_index = GetFirstNonSpace(str, curr_index + 3);  // shift to "("

      if (curr_index == str.size() || str[curr_index] != '(') {
        throw MyException(ErrorCode::kSyntaxError,
                          "expected opening bracket not found");
      }

      std::string_view log_str = str.substr(curr_index, str.size());
      int distance_to_closing_bracket = GetDistanceToClosingBracket(log_str);
      int distance_to_comma = GetDistanceToComma(log_str);

      // adding the first argument
      AppendArgumentOfLogOrSqrt(str, curr_index, distance_to_comma, ')',
                                h_list);
      // adding the second argument
      AppendArgumentOfLogOrSqrt(str, curr_index + distance_to_comma,
                                distance_to_closing_bracket - distance_to_comma,
                                '(', h_list);
      Append(h_list);
      shift = distance_to_closing_bracket + 1;

    } else if (IsSqrt(str.substr(curr_index, str.size()))) {
      std::shared_ptr<HierarchicalList> h_list(new HierarchicalList());
      h_list->Append(TypeOfObject::kSqrt);  // adding the operation

      curr_index = GetFirstNonSpace(str, curr_index + 4);  // shift to "("

      if (curr_index == str.size() || str[curr_index] != '(') {
        throw MyException(ErrorCode::kSyntaxError,
                          "expected opening bracket not found");
      }

      std::string_view sqrt_str = str.substr(curr_index, str.size());
      int distance_to_closing_bracket = GetDistanceToClosingBracket(sqrt_str);

      // adding the argument
      AppendArgumentOfLogOrSqrt(str, curr_index, distance_to_closing_bracket,
                                ' ', h_list);
      Append(h_list);
      shift = distance_to_closing_bracket + 1;

    } else if (shift = IsNumber(str.substr(curr_index, str.size()))) {
      Append(stoll((std::string)str.substr(curr_index, str.size())));

    } else if (shift = IsVariable(str.substr(curr_index, str.size()))) {
      Append(TypeOfObject::kVariable);

    } else {
      throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
    }

    if (count_of_brackets < 0) {
      throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
    }

    first_iteration = false;
    curr_index += shift;
    shift = 1;  // default shift

    curr_index = GetFirstNonSpace(str, curr_index);
  }

  if (count_of_brackets > 0) {
    throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
  }
}

const Node& HierarchicalList::GetHead() const {
  if (head_ == nullptr) {
    throw MyException(ErrorCode::kRuntimeError, "empty list");
  }
  return *head_;
}

void HierarchicalList::AppendArgumentOfLogOrSqrt(
    std::string_view str, int begin, int dist, char sym,
    std::shared_ptr<HierarchicalList>& h_list) {
  std::string temp(str.substr(begin, 1 + dist));
  std::string_view temp_view = temp.substr(1, dist - 1);
  if (!temp_view.size()) {
    throw MyException(ErrorCode::kSyntaxError, "not enough arguments");
  }
  temp_view.remove_prefix(GetFirstNonSpace(temp_view, 0));
  int shift = IsNumber(temp_view);
  if (GetFirstNonSpace(temp_view, shift) ==
      temp_view.size()) {  // adding a number
    h_list->Append(stoll((std::string)temp_view));
  } else {
    if (sym == '(') {
      temp.front() = sym;
    } else if (sym == ')') {
      temp.back() = sym;
    }
    std::shared_ptr<HierarchicalList> h_list_child(new HierarchicalList(temp));
    h_list->Append(h_list_child);
  }
}

template <typename T>
void HierarchicalList::Append(T object) {
  if (head_ == nullptr) {
    head_ = std::make_shared<Node>(object);
    end_ = head_;
  } else {
    end_->next_ = std::make_shared<Node>(object);
    end_ = end_->next_;
  }
}

int HierarchicalList::GetDistanceToClosingBracket(std::string_view str) {
  int count_of_brackets = 0;
  bool first_bracket = true;
  int closing_bracket = str.size();

  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      ++count_of_brackets;
      first_bracket = false;
    } else if (str[i] == ')') {
      --count_of_brackets;
    }

    if (count_of_brackets < 0) {
      throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
    }

    if (!count_of_brackets && !first_bracket) {
      closing_bracket = i;
      break;
    }
  }

  if (count_of_brackets > 0) {
    throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
  }

  return closing_bracket;
}

int HierarchicalList::GetFirstNonSpace(std::string_view str, int pos) {
  for (; pos < str.size(); ++pos) {
    if (!isspace(str[pos])) return pos;
  }
  return str.size();
}

int HierarchicalList::GetDistanceToComma(std::string_view str) {
  int count_of_brackets = 0;
  bool first_bracket = true;
  int distance_to_comma = str.size();

  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      ++count_of_brackets;
      first_bracket = false;
    } else if (str[i] == ')') {
      --count_of_brackets;
    }

    if (count_of_brackets < 0) {
      throw MyException(ErrorCode::kSyntaxError, "invalid syntax");
    }

    if (count_of_brackets == 1 && str[i] == ',') {
      distance_to_comma = i;
      break;
    }
  }

  if (distance_to_comma == str.size()) {
    throw MyException(ErrorCode::kSyntaxError, "expected comma not found");
  }

  return distance_to_comma;
}

bool HierarchicalList::CompareStrings(std::string_view str, NamesType type) {
  return str.substr(0, names_[(int)type].size()) == names_[(int)type];
}

int HierarchicalList::IsVariable(std::string_view str) {
  int i = 0;
  for (; i < str.size() &&
         (std::isalpha(str[i]) || (str[i] == '_') || (isdigit(str[i]) && i));
       ++i)
    ;
  return i;
}

int HierarchicalList::IsNumber(std::string_view str) {
  bool is_negative = false;
  int i = 0;

  if (1 < str.size() && str[i] == '-' && (i + 1) < str.size() &&
      isdigit(str[i + 1])) {
    is_negative = true;
    ++i;
  }

  for (; i < str.size() && isdigit(str[i]); ++i)
    ;

  if ((i < str.size() && (str[i] == '_' || std::isalpha(str[i])))) {
    i = 0;
  }

  if (i && ((!is_negative && i > 18) || (is_negative && i > 19))) {
    throw MyException(ErrorCode::kValueError, "too big number");
  }

  return i;
}

bool HierarchicalList::IsSqrt(std::string_view str) {
  return CompareStrings(str, NamesType::kSqrt);
}

bool HierarchicalList::IsLog(std::string_view str) {
  return CompareStrings(str, NamesType::kLog);
}