#include "parser.h"

#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    using namespace tc;

    const int MAX_CHAR = 512;
    errno_t err = 0;
    char input_str[MAX_CHAR] = "";
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("  TinyCalc [filename]\n");
            goto END;
        } else {
            FILE* fp;
#ifdef _MSC_VER
            err = fopen_s(&fp, argv[i], "r");
#else
            fp = fopen(argv[i], "r");
#endif
            if (err) {
                fclose(fp);
                fprintf(stderr, "failed open file: %s\n", argv[i]);
                goto END;
            }
            for (int j = 0, c = 0; ; ++j) {
                c = getc(fp);
                if (c == EOF) {
                    break;
                }
                input_str[j] = c;
            }
            fclose(fp);

            printf("%s\n", input_str);
            Lexer lexer(input_str);
            err = lexer.getError();
            if (err) {
                fprintf(stderr, "failed lex\n");
                goto END;
            }
            lexer.print();

            Parser parser(lexer.getItems());
            err = parser.parse();
            if (err) {
                fprintf(stderr, "failed parse\n");
                goto END;
            }
            double d = parser.getValue();
            printf("%.15f\n\n", d);
            goto END;
        }
    }

    for (;;) {
        printf("> ");
        fgets(input_str, MAX_CHAR, stdin);
        fflush(stdin);
        input_str[strlen(input_str) - 1] = '\0';

        if (strcmp(input_str, "") == 0 || strcmp(input_str, "q") == 0) {
            printf("exit\n");
            goto END;
        }

        Lexer lexer(input_str);
        err = lexer.getError();
        if (err) {
            fprintf(stderr, "failed lex\n");
            continue;
        }
        lexer.print();

        Parser parser(lexer.getItems());
        err = parser.parse();
        if (err) {
            fprintf(stderr, "failed parse\n");
            continue;
        }
        double d = parser.getValue();
        printf("%.15f\n\n", d);
    }

END:
    //system("pause");

    return err;
}