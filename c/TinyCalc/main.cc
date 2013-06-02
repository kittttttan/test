#include "parser.h"

#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    using namespace tc;

    errno_t err = 0;
    static const size_t MAX_CHAR = 512;
    char input_str[MAX_CHAR] = "";
    bool debug = false;
    
    // option
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("  TinyCalc [-d] [filename]\n");
            goto END;
        } else if (!strcmp(argv[i], "-d")) {
          printf("debug mode\n");
            debug = true;
        } else {
            FILE* fp;
#ifdef _MSC_VER
            err = fopen_s(&fp, argv[i], "r");
            if (err) {
#else
            fp = fopen(argv[i], "r");
            if (!fp) {
#endif
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
            if (debug) { lexer.print(); }

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

    // main loop
    for (;;) {
        printf("> ");
        fgets(input_str, MAX_CHAR, stdin);
        fflush(stdin);
        input_str[strlen(input_str) - 1] = '\0';

        if (!strcmp(input_str, "") || !strcmp(input_str, "q")) {
            printf("exit\n");
            goto END;
        }

        Lexer lexer(input_str);
        err = lexer.getError();
        if (err) {
            fprintf(stderr, "failed lex\n");
            continue;
        }
        if (debug) { lexer.print(); }

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