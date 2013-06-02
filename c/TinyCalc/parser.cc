#include "parser.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace tc {

using namespace std;

const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

Parser::Parser(const vector<Lexer::Item>& items) :
    index_(0),
    err_(0),
    value_(0.0)
{
    items_ = items;
}

Parser::~Parser()
{

}

errno_t Parser::parse()
{
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

double Parser::number()
{
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

    switch (items_[index_].type) {
    case Lexer::INTEGER:
        {
            long n = atol(items_[index_].value.c_str());
            res = static_cast<double>(n);
        }
        break;
    case Lexer::DECIMAL:
        res = atof(items_[index_].value.c_str());
        break;
    case  Lexer::PI:
        res = PI;
        break;
    case Lexer::E:
        res = E;
        break;
    default:
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

double Parser::factor()
{
    int func = 0;

    switch (items_[index_].type) {
    case Lexer::ABS:
        func = Lexer::ABS;
        ++index_;
        break;
    case Lexer::SQRT:
        func = Lexer::SQRT;
        ++index_;
        break;
    case Lexer::SIN:
        func = Lexer::SIN;
        ++index_;
        break;
    case Lexer::COS:
        func = Lexer::COS;
        ++index_;
        break;
    case Lexer::TAN:
        func = Lexer::TAN;
        ++index_;
        break;
    case Lexer::ASIN:
        func = Lexer::ASIN;
        ++index_;
        break;
    case Lexer::ACOS:
        func = Lexer::ACOS;
        ++index_;
        break;
    case Lexer::ATAN:
        func = Lexer::ATAN;
        ++index_;
        break;
    case Lexer::SINH:
        func = Lexer::SINH;
        ++index_;
        break;
    case Lexer::COSH:
        func = Lexer::COSH;
        ++index_;
        break;
    case Lexer::TANH:
        func = Lexer::TANH;
        ++index_;
        break;
    case Lexer::LOG:
        func = Lexer::LOG;
        ++index_;
        break;
    case Lexer::LOG10:
        func = Lexer::LOG10;
        ++index_;
        break;
    case Lexer::EXP:
        func = Lexer::EXP;
        ++index_;
        break;
    default:
        break;
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

        switch (func) {
        case Lexer::ABS: return abs(res);
        case Lexer::SQRT: return sqrt(res);
        case Lexer::SIN: return sin(res);
        case Lexer::COS: return cos(res);
        case Lexer::TAN: return tan(res);
        case Lexer::ASIN: return asin(res);
        case Lexer::ACOS: return acos(res);
        case Lexer::ATAN: return atan(res);
        case Lexer::SINH: return sinh(res);
        case Lexer::COSH: return cosh(res);
        case Lexer::TANH: return tanh(res);
        case Lexer::LOG: return log(res);
        case Lexer::LOG10: return log10(res);
        case Lexer::EXP: return exp(res);
        }

        if (items_[index_].type == Lexer::POW) {
            ++index_;
            res = pow(res, factor());
        }

        return res;
    }

    return number();
}

double Parser::term()
{
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

double Parser::expression()
{
    double res = term();

    for (;;) {
        switch (items_[index_].type) {
        case Lexer::PLUS:
            ++index_;
            res += term();
            break;
        case Lexer::MINUS:
            ++index_;
            res -= term();
            break;
        default:
            return res;
        }
    }

    return res;
}

} // namespace tc