#pragma once
#include <vector>
#include <cerrno>
#include <string>

namespace tc {

class Lexer {
public:
    static const char* typeNames[];
    enum Type {
        INTEGER = 0,
        DECIMAL,

        PARE_OP,
        PARE_CL,

        PLUS,
        MINUS,
        MUL,
        DIV,
        MOD,
        POW,

        LITERAL,
        PI,
        E,

        ABS,
        SQRT,
        SIN,
        COS,
        TAN,
        ASIN,
        ACOS,
        ATAN,
        SINH,
        COSH,
        TANH,
        LOG,
        LOG10,
        EXP,

        END
    };
    enum Status {
        EMPTY = 0,
        INT,
        FLOAT,
        OPE,
        WORD,
    };
    struct Item {
        int line;
        int pos;
        Type type;
        std::string value;
    };

public:
    explicit Lexer(const char*);
    ~Lexer();

    std::vector<Item> getItems() const { return items_; }
    errno_t getError() const { return err_; }
    void print();

private:
    const char* src_;
    int index_;
    int line_;
    int pos_;
    size_t length_;
    errno_t err_;
    Status status_;
    std::vector<Item> items_;

    errno_t lex();
    errno_t setLiteral(Type&, const char*);
};

} // namespace tc