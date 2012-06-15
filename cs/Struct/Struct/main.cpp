#include <stdio.h>
#include <wchar.h>
#include <locale.h>

typedef struct _Sample {
  int i;
  wchar_t c[16];
  float f;
} Sample;

void writeStruct(const char* filename) {
  Sample s = {7, L"奈々", 7.7};
  FILE* fp;
  
  fp = fopen(filename, "wb");
  if (!fp) { fprintf(stderr, "can't open %s.\n", filename); return; }
  fwrite(&s, sizeof(s), 1, fp);
  
  fclose(fp);
}

void readStruct(const char* filename) {
  Sample s;
  FILE* fp;
  
  fp = fopen(filename, "rb");
  if (!fp) { fprintf(stderr, "can't open %s.\n", filename); return; }
  fread(&s, sizeof(s), 1, fp);
  
  fclose(fp);

  wprintf(
    L"i: %d\n"
    L"s: %s\n"
    L"f: %f\n",
    s.i, s.c, s.f);
}

void help(char* app) {
  puts("Usage:");
  printf("  %s [l|s] filename\n", app);
  puts("Option:");
  puts("  l Load");
  puts("  s Save");
}

int main(int argc, char** argv) {
  setlocale(LC_ALL, "Japanese");

  if (argc > 2) {
    if (argv[1][0] == 'l') {
      printf("load %s\n", argv[2]);
      readStruct(argv[2]);
    } else if (argv[1][0] == 's') {
      printf("save %s\n", argv[2]);
      writeStruct(argv[2]);
    } else {
      help(argv[0]);
    }
  } else {
    help(argv[0]);
  }

  return 0;
}