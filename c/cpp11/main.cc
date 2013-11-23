/**
 * C++11 Features in Visual C++ 11
 * http://blogs.msdn.com/b/vcblog/archive/2011/09/12/10209291.aspx
 *
 * C++11
 * http://en.wikipedia.org/wiki/C%2B%2B11
 */

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <regex>
#include <random>

const int elementCount = 9;

struct RValue{
    void print() const {
        printf("RValue&& rvalue = RValue();\n");
    }
};

auto add(int a, int b) -> int {
    return a + b;
}

template<bool Test> class SomeType { };

extern template class std::vector<RValue>;

void nullptr_test(int n) {
    printf("call " __FUNCSIG__ "\n");
}
void nullptr_test(char* n) {
    printf("call " __FUNCSIG__ "\n");
}

// extended friend
template <class T>
class X {
    friend T;
};

// override and final
struct Base {
    Base() = default;
    Base(const Base&) = delete;
    virtual void some_func(int);
    virtual void final_func() final;
};

struct Derived : Base {
    virtual void some_func(int) override;
    //virtual void some_func(float) override;
    //void final_func();
};

class InitList {
public:
    InitList() { }
    InitList(std::initializer_list<int> list) {
        std::for_each(list.begin(), list.end(), [](int n) { printf("%d\n", n); });
    }
};
void func_init_list(std::initializer_list<int> list) {
    std::for_each(list.begin(), list.end(), [](int n) { printf("%d\n", n); });
}

int main() {
    printf("** Rvalue references **\n");
    const RValue&& rvalue = RValue();
    rvalue.print();

    printf("\n** Trailing return types **\n");
    const int a = 1;
    const int b = 2;
    printf("%d + %d = %d\n", a, b, add(a, b));

    printf("\n** Lambdas **\n");
    static_assert(elementCount > 1, "elementCount > 1");
    std::vector<int> v(elementCount, 1);
    int x = 1;
    int y = 1;

    const auto pr = [](int x){ printf("%d\n", x); };
    const auto fib = [=]() mutable throw() -> int {  
        // Generate current value.
        int n = x + y;

        // Update previous two values.
        x = y;
        y = n;

        return n;
    };
    std::generate_n(v.begin() + 2, elementCount - 2, fib);
    std::for_each(v.begin(), v.end(), pr);

    printf("\n** Right angle brackets **\n");
    // illegal
    //std::vector<SomeType<1>2>> x1;

    // legal
    const std::vector<SomeType<(1>2)>> x1;

    //printf("\n** Extern templates **\n");

    printf("\n** nullptr **\n");
    nullptr_test(nullptr);

    printf("\n** Strongly typed enums **\n");
    enum Enumeration : unsigned short { Val1, };
    printf("%d\n", sizeof(Val1));

    // printf("\n** Alignment **\n");
    // http://blogs.msdn.com/b/vcblog/archive/2011/09/12/10209291.aspx

    //printf("\n** Extended friend declarations **\n");

    printf("\n** Local and unnamed types as template arguments **\n");
    struct Local {
        int value;
        void print() const {
            printf("Local\n");
        }
    };

    Local lo = {1};
    //printf("sizeof(Local::value) = %d\n", sizeof(Local::value));
    const std::vector<Local> vec(1, Local());
    vec.front().print();

    printf("\n** exception_ptr **\n");
    std::exception_ptr ep;
    ep = std::current_exception();
    try {
        std::rethrow_exception(ep);
    } catch (std::exception const& e) {
        printf("%s\n", e.what());
    }

    printf("\n** Range-based for-loop **\n");
    int my_array[] = {0,1,2,3,4,5,6};
    for (int& x : my_array) {
    	++x;
    }
    for (int& x : my_array) {
    	printf("%d\n", x);
    }

    InitList list({1, 2, 3});
    func_init_list({1,2,3});

    printf("\n** regex **\n");
    std::regex re("\\d+");
    std::match_results<const char *> results;
    char* src = "mm123456nn7";
    if (!std::regex_search(src, results, re, std::regex_constants::match_default)) {
        return 1;
    }

    printf("prefix: %s\n", results.prefix().str().c_str());
    printf("suffix: %s\n", results.suffix().str().c_str());
    printf("posision: %d\n", results.position());
    printf("str: %s\n", results.str().c_str());

    for (auto it = results.begin(); it != results.end(); ++it) {
        if (it->matched) {
            printf("sub_match: %s\n", it->str().c_str());
        }
    }

    std::regex re2("[^\\d]+");
    std::string replaced = std::regex_replace(std::string(src), re2, std::string(""),
        std::regex_constants::match_default);
    printf("%s\n", replaced.c_str());

    printf("\n** random **\n");
    std::uniform_int_distribution<int> dist(0, 99);
    std::mt19937 engine; // Mersenne twister MT19937
    for (int i = 0; i < 7; ++i) {
        int rand = dist(engine);
        printf("%d\n", rand);
    }

    system("pause");

    return 0;
}