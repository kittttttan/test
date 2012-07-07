/**
 * WCHAR to UTF-8
 * UTF-8 to WCHAR
 */
#include <stdio.h>
#include <Windows.h>
#include <locale.h>

#define MAX_CHAR    1024
#define OUTPUT_FILE L"test.txt"

int main(int argc, char** argv) {
    FILE* fp;
    errno_t err;
    WCHAR str[] = L"…Ž÷“ÞX\n";
    char utf[MAX_CHAR];
    char c;
    size_t size, sizeRequired;

    setlocale(LC_ALL, "Japanese");

    printf("s - Save    l - Load\n");
    scanf_s("%c", &c, 1);

    switch (c) {
    case 's': {
        size_t wcsChars = wcslen(str);

        printf("encode UTF-8\n");

        sizeRequired = WideCharToMultiByte(
            CP_UTF8, 0, str, wcsChars, NULL, 0, NULL, NULL);
        WideCharToMultiByte(CP_UTF8, 0, str, wcsChars, utf, sizeRequired, NULL, NULL);

        err = _wfopen_s(&fp, OUTPUT_FILE, L"ab");
        if (err != 0) {
            fprintf(stderr, "Failed to open file.\n");
            system("pause");
            return -1;
        }

        fwrite(utf, sizeRequired, 1, fp);
        fclose(fp);

        wprintf(L"Save as " OUTPUT_FILE L"\n");

        break;
        }
    case 'l': {
        WCHAR wc[MAX_CHAR] = L"";
        long fsize;

        printf("decode UTF-8\n");

        err = _wfopen_s(&fp, OUTPUT_FILE, L"rb");
        if (err != 0) {
            fprintf(stderr, "Failed to open file.\n");
            system("pause");
            return -1;
        }

        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (fsize > MAX_CHAR) {
            fprintf(stderr, "WARN: Can't read over %d bytes\n", MAX_CHAR);
            fsize = MAX_CHAR;
        }

        fread(utf, fsize, 1, fp);
        fclose(fp);

        printf("load %u bytes\n", fsize);

        size = MultiByteToWideChar(CP_UTF8, 0, utf, fsize, NULL, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf, fsize, wc, size);

        wprintf(L"%s\n", wc);
        break;
        }
    default:
        printf("Exit\n");
        break;
    }

    system("pause");

    return 0;
}