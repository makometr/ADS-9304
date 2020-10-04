#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>

enum Mode
{
    kStart = 0,
    kOper = 1,
    kNumber = 2,
    kNothing = -1
};

struct Object
{
    Mode mode;
    char ch;
    Object() : mode(kStart), ch(0) {}
};

class Analyzer
{
    const std::string &str;
    size_t index;
    size_t lastIndex;
    Object oldMode;
    inline void skipSome(const char *thing);

public:
    const bool analyzeCnstExpr();
    Analyzer(const std::string &otherStr, size_t start = 0, size_t end = std::string::npos);
    ~Analyzer() = default;
};

#endif