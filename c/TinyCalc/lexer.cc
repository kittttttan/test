#include "lexer.h"

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cassert>

namespace tc {

namespace {
    const int MAX_VALUE_CHAR_LENGTH = 256;
}

const char* Lexer::typeNames[] = {
    "Integer",
    "Decimal",

    "PareOp",
    "PareCl",

    "Plus",
    "Minus",
    "Multi",
    "Div",
    "Modulo",
    "Power",

    "Literal",

    // constant
    "pi",
    "e",

    // function
    "abs",
    "sqrt",
    "sin",
    "cos",
    "tan",
    "asin",
    "acos",
    "atan",
    "sinh",
    "cosh",
    "tanh",
    "log",
    "log10",
    "exp",

    "End"
};

Lexer::Lexer(const char* src) :
    index_(0),
    line_(0),
    pos_(0),
    length_(0),
    err_(0),
    status_(EMPTY)
{
    src_ = src;
    err_ = lex();
}

Lexer::~Lexer() {

}

errno_t Lexer::lex() {
    errno_t err = 0;
    int c;
    char cur[MAX_VALUE_CHAR_LENGTH];
    Item item = {0};

    for (;; ++index_, ++pos_) {
        c = src_[index_];

        if (isdigit(c)) {
            cur[length_] = c;
            ++length_;
            if (status_ != FLOAT && status_ != WORD) {
                status_ = INT;
            }
        } else if (c == '.') {
            cur[length_] = c;
            ++length_;
            if (status_ == FLOAT) {
                cur[length_] = '\0';
                fprintf(stderr, "(%3d,%3d)Invalid float: %s\n",
                    line_, pos_, cur);
                err = 1;
                goto LEX_END;
            }
            status_ = FLOAT;
        } else {
            if (status_ == INT || status_ == FLOAT) {
                cur[length_] = '\0';
                ++length_;

                if (status_ == INT) {
                    item.type = INTEGER;
                } else if (status_ == FLOAT) {
                    item.type = DECIMAL;
                }
                item.value = cur;
                item.line = line_;
                item.pos = pos_ - length_ + 1;
                items_.push_back(item);

                length_ = 0;
            }

            if (c == '+' || c == '-') {
                if (status_ == WORD) {
                    cur[length_] = '\0';
                    ++length_;

                    if (setLiteral(item.type, cur)) {
                        err = 3;
                        fprintf(stderr, "(%3d,%3d)undefined literal: %s\n",
                            line_, pos_ - length_ + 1, cur);
                        goto LEX_END;
                    }
                    //item.type = LITERAL;
                    item.value = cur;
                    item.line = line_;
                    item.pos = pos_ - length_ + 1;
                    items_.push_back(item);

                    length_ = 0;
                }

                if (c == '+') {
                    item.type = PLUS;
                } else if (c == '-') {
                    item.type = MINUS;
                }
                item.value = c;
                item.line = line_;
                item.pos = pos_;
                items_.push_back(item);
                length_ = 0;
                status_ = EMPTY;
            } else if (c == '*' || c == '/' || c == '%' || c == '^'
                    || c == '(' || c == ')') {
                if (status_ == WORD) {
                    cur[length_] = '\0';
                    ++length_;

                    if (setLiteral(item.type, cur)) {
                        err = 3;
                        fprintf(stderr, "(%3d,%3d)undefined literal: %s\n",
                            line_, pos_ - length_ + 1, cur);
                        goto LEX_END;
                    }
                    //item.type = LITERAL;
                    item.value = cur;
                    item.line = line_;
                    item.pos = pos_ - length_ + 1;
                    items_.push_back(item);

                    length_ = 0;
                }

                if (c == '*') {
                    item.type = MUL;
                } else if (c == '/') {
                    item.type = DIV;
                } else if (c == '%') {
                    item.type = MOD;
                } else if (c == '^') {
                    item.type = POW;
                } else if (c == '(') {
                    item.type = PARE_OP;
                } else if (c == ')') {
                    item.type = PARE_CL;
                }
                item.value = c;
                item.line = line_;
                item.pos = pos_;
                items_.push_back(item);
                length_ = 0;
                status_ = EMPTY;
            } else if (c == '\0') {
                if (status_ == WORD) {
                    cur[length_] = '\0';
                    ++length_;

                    if (setLiteral(item.type, cur)) {
                        err = 3;
                        fprintf(stderr, "(%3d,%3d)undefined literal: %s\n",
                            line_, pos_ - length_ + 1, cur);
                        goto LEX_END;
                    }
                    //item.type = LITERAL;
                    item.value = cur;
                    item.line = line_;
                    item.pos = pos_ - length_ + 1;
                    items_.push_back(item);

                    length_ = 0;
                }
                break;
            } else if (c == '\n') {
                ++line_;
                pos_ = -1;
                if (status_ == WORD) {
                    cur[length_] = '\0';
                    ++length_;

                    if (setLiteral(item.type, cur)) {
                        err = 3;
                        fprintf(stderr, "(%3d,%3d)undefined literal: %s\n",
                            line_, pos_ - length_ + 1, cur);
                        goto LEX_END;
                    }
                    item.value = cur;
                    item.line = line_;
                    item.pos = pos_ - length_ + 1;
                    items_.push_back(item);

                    length_ = 0;
                }
                status_ = EMPTY;
            } else if (c == ' ' || c == '\t' || c == '\r') {
                if (status_ == WORD) {
                    cur[length_] = '\0';
                    ++length_;

                    if (setLiteral(item.type, cur)) {
                        err = 3;
                        fprintf(stderr, "(%3d,%3d)undefined literal: %s\n",
                            line_, pos_ - length_ + 1, cur);
                        goto LEX_END;
                    }
                    item.value = cur;
                    item.line = line_;
                    item.pos = pos_ - length_ + 1;
                    items_.push_back(item);

                    length_ = 0;
                }
                status_ = EMPTY;
            } else if (isalpha(c)) {
                cur[length_] = c;
                ++length_;
                status_ = WORD;
            } else {
                fprintf(stderr, "(%3d,%3d)Invalid: %c\n", line_, pos_, c);
                err = 2;
                goto LEX_END;
            }
        }

        assert(length_ < MAX_VALUE_CHAR_LENGTH);
    }

LEX_END:
    item.type = END;
    item.value = '\0';
    item.line = line_;
    item.pos = pos_;
    items_.push_back(item);

    return err;
}

errno_t Lexer::setLiteral(Type& type, const char* lit) {
    errno_t err = 0;
    if (strcmp(lit, "pi") == 0) {
        type = PI;
    } else if (strcmp(lit, "e") == 0) {
        type = E;
    } else if (strcmp(lit, "abs") == 0) {
        type = ABS;
    } else if (strcmp(lit, "sqrt") == 0) {
        type = SQRT;
    } else if (strcmp(lit, "sin") == 0) {
        type = SIN;
    } else if (strcmp(lit, "cos") == 0) {
        type = COS;
    } else if (strcmp(lit, "tan") == 0) {
        type = TAN;
    } else if (strcmp(lit, "asin") == 0) {
        type = ASIN;
    } else if (strcmp(lit, "acos") == 0) {
        type = ACOS;
    } else if (strcmp(lit, "atan") == 0) {
        type = ATAN;
    } else if (strcmp(lit, "sinh") == 0) {
        type = SINH;
    } else if (strcmp(lit, "cosh") == 0) {
        type = COSH;
    } else if (strcmp(lit, "tanh") == 0) {
        type = TANH;
    } else if (strcmp(lit, "log") == 0) {
        type = LOG;
    } else if (strcmp(lit, "log10") == 0) {
        type = LOG10;
    } else if (strcmp(lit, "exp") == 0) {
        type = EXP;
    } else {
        err = 1;
    }

    return err;
}

void Lexer::print() {
    for (std::vector<Item>::iterator it = items_.begin();
            it != items_.end(); ++it) {
        printf("(%3d,%3d)%7s: %s\n",
            it->line, it->pos,
            typeNames[it->type], it->value.c_str());
    }
}

} // namespace tc