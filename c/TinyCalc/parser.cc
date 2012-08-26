#include "parser.h"

//#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace tc {

using namespace std;

Parser::Parser(const std::vector<Lexer::Item>& items) :
    index_(0),
    err_(0),
    value_(0.0)
{
    items_ = items;
}

Parser::~Parser() {

}

errno_t Parser::parse() {
    err_ = 0;
    index_ = 0;
    value_ = expression();

    if (items_[index_].type != Lexer::END) {
        err_ = 3;
        fprintf(stderr, "%d: abort at (%d,%d)\n",
            index_, items_[index_].line, items_[index_].pos);
    }

    return err_;
}

double Parser::number() {
    double res = 0.0;
    bool sign = true;
    for (;;) {
        if (items_[index_].type == Lexer::END) {
            err_ = 4;
            fprintf(stderr, "%d: missing number, or extra sign\n", index_ - 1);
            return res;
        } else if (items_[index_].type == Lexer::PLUS) {
            ++index_;
        } else if (items_[index_].type == Lexer::MINUS) {
            ++index_;
            sign = !sign;
        } else {
            break;
        }
    }

    if (items_[index_].type == Lexer::INTEGER) {
        long n = atol(items_[index_].value.c_str());
        res = static_cast<double>(n);
    } else if (items_[index_].type == Lexer::DECIMAL) {
        res = atof(items_[index_].value.c_str());
    } else if (items_[index_].type == Lexer::PI) {
        res = M_PI;
    } else if (items_[index_].type == Lexer::E) {
        res = M_E;
    } else {
        fprintf(stderr, "invalid number\n");
        err_ = 4;
        return res;
    }
    ++index_;

    if (items_[index_].type == Lexer::POW) {
        ++index_;
        res = pow(res, factor());
    }

    if (!sign) {
        res = -res;
    }

    return res;
}

double Parser::factor() {
    int func = 0;
    if (items_[index_].type == Lexer::ABS) {
        func = Lexer::ABS;
        ++index_;
    } else if (items_[index_].type == Lexer::SQRT) {
        func = Lexer::SQRT;
        ++index_;
    } else if (items_[index_].type == Lexer::SIN) {
        func = Lexer::SIN;
        ++index_;
    } else if (items_[index_].type == Lexer::COS) {
        func = Lexer::COS;
        ++index_;
    } else if (items_[index_].type == Lexer::TAN) {
        func = Lexer::TAN;
        ++index_;
    } else if (items_[index_].type == Lexer::ASIN) {
        func = Lexer::ASIN;
        ++index_;
    } else if (items_[index_].type == Lexer::ACOS) {
        func = Lexer::ACOS;
        ++index_;
    } else if (items_[index_].type == Lexer::ATAN) {
        func = Lexer::ATAN;
        ++index_;
    } else if (items_[index_].type == Lexer::SINH) {
        func = Lexer::SINH;
        ++index_;
    } else if (items_[index_].type == Lexer::COSH) {
        func = Lexer::COSH;
        ++index_;
    } else if (items_[index_].type == Lexer::TANH) {
        func = Lexer::TANH;
        ++index_;
    } else if (items_[index_].type == Lexer::LOG) {
        func = Lexer::LOG;
        ++index_;
    } else if (items_[index_].type == Lexer::LOG10) {
        func = Lexer::LOG10;
        ++index_;
    } else if (items_[index_].type == Lexer::EXP) {
        func = Lexer::EXP;
        ++index_;
    }

    if (items_[index_].type == Lexer::PARE_OP) {
        ++index_;
        double res = expression();
        if (items_[index_].type != Lexer::PARE_CL) {
            err_ = 1;
            fprintf(stderr, "%d: missing )\n", index_);
            return 0.0;
        }
        ++index_;

        if (func == Lexer::ABS) { return abs(res); }
        if (func == Lexer::SQRT) { return sqrt(res); }
        if (func == Lexer::SIN) { return sin(res); }
        if (func == Lexer::COS) { return cos(res); }
        if (func == Lexer::TAN) { return tan(res); }
        if (func == Lexer::ASIN) { return asin(res); }
        if (func == Lexer::ACOS) { return acos(res); }
        if (func == Lexer::ATAN) { return atan(res); }
        if (func == Lexer::SINH) { return sinh(res); }
        if (func == Lexer::COSH) { return cosh(res); }
        if (func == Lexer::TANH) { return tanh(res); }
        if (func == Lexer::LOG) { return log(res); }
        if (func == Lexer::LOG10) { return log10(res); }
        if (func == Lexer::EXP) { return exp(res); }
        if (items_[index_].type == Lexer::POW) {
            ++index_;
            res = pow(res, factor());
        }

        return res;
    }

    return number();
}

double Parser::term() {
    double res = factor();
    for (;;) {
        if (items_[index_].type == Lexer::MUL) {
            ++index_;
            res *= factor();
        } else if (items_[index_].type == Lexer::POW) {
            ++index_;
            res = pow(res, factor());
        } else if (items_[index_].type == Lexer::DIV) {
            ++index_;
            double d = factor();
            if (d == 0.0) {
                err_ = 2;
                fprintf(stderr, "%d: zero division\n", index_ - 1);
                return 0.0;
            }
            res /= d;
        } else if (items_[index_].type == Lexer::MOD) {
            ++index_;
            double d = factor();
            if (d == 0.0) {
                err_ = 2;
                fprintf(stderr, "%d: zero division\n", index_ - 1);
                return 0.0;
            }
            int q = static_cast<int>(res / d);
            if (res < 0.0) {
                res = res + abs(q * d);
            } else {
                res = res - abs(q * d);
            }
        } else {
            break;
        }
    }
    return res;
}

double Parser::expression() {
    double res = term();
    for (;;) {
        if (items_[index_].type == Lexer::PLUS) {
            ++index_;
            res += term();
        } else if (items_[index_].type == Lexer::MINUS) {
            ++index_;
            res -= term();
        } else {
            break;
        }
    }

    return res;
}

} // namespace tc