#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace std {

static void getline(char *line, FILE *fin)
{
  int c = '\0', cur = 0;
  while (c != '\n' && (c = fgetc(fin)) != EOF) {
    line[cur++] = c;
  }
  line[cur] = '\0';
}

}

using namespace std;

int main(int argc, char **argv)
{
  char line[80];
  int c;
  // Fix num lines, num columns, strdup-1

  FILE *fin = fopen("bible.txt", "r+");
  FILE *fout = fopen("copy.txt", "w+");  

  if (fin != NULL) {

    c = fgetc(fin);

    while (c != EOF) {
      fputc(c, fout);
      c = fgetc(fin);
    }

    fclose(fin);
    fclose(fout);

  } else {
    printf("%s\n", "File pointer is null!");
  }

  return 0;
}

// Source
// https://stackoverflow.com/a/31132653/5305519

// Debug

// (gdb) run
// Starting program: /home/jarye821/Repositories/tdde45-lab5/debugging/fileutil
// Program received signal SIGSEGV, Segmentation fault.
// _IO_feof (fp=0x0) at feof.c:35
// 35      feof.c: No such file or directory.
