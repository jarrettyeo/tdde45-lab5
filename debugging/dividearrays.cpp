#include <random>

int main(int argc, char **argv)
{
  std::random_device generator;
  std::uniform_int_distribution<int> intdist(0,50);
  double res[1024];

  for (int i=0; i<1024; i++) {
    int nom = intdist(generator);
    int denom = intdist(generator);
    res[i] = nom / denom;
  }
  return 0;
}

// Debug

// (gdb) break 14
// Breakpoint 1 at 0xbdd: file dividearrays.cpp, line 14.
// (gdb) run
// Starting program: /home/jarye821/Repositories/tdde45-lab5/debugging/dividearrays

// Program received signal SIGFPE, Arithmetic exception.
// 0x0000555555554bb9 in main (argc=1, argv=0x7fffffffe048) at dividearrays.cpp:12
// warning: Source file is more recent than executable.
// 12          res[i] = nom / denom;
// (gdb) print denom
// $1 = 0