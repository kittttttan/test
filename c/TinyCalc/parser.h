#pragma once
#include "lexer.h"
#include <vector>

namespace tc {

class Parser {
public:
    Parser(const std::vector<Lexer::Item>&);
    ~Parser();

    errno_t getError() const { return err_; }
    double getValue() const { return value_; }
    errno_t parse();

private:
    std::vector<Lexer::Item> items_;
    int index_;
    errno_t err_;
    double value_;

    double number();
    double factor();
    double term();
    double expression();
};

} // namespace tc