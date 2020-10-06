#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>

enum Status
{
    kNothing,
    kStart,
    kOper,
    kNumber
};

class Analyzer
{
    const std::string &str;
    size_t index;
    size_t lastIndex;
    Status oldObjStatus;
    inline void skipSome(const char *thing);

public:
    const bool operator()();
    Analyzer(const std::string &otherStr, size_t start = 0, size_t end = std::string::npos);
    ~Analyzer() = default;
};

#endif