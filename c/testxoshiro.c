#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xoshiro256pp.h"

int main(int argc, const char* argv[]) {
  int n = 10;
  if (argc == 2) n = atoi(argv[1]);

  for (int i = 0; i < n; i++)
    printf("%016lx\n", next());

  return 0;
}
