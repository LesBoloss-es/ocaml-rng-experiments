#include <stdlib.h>
#include <stdio.h>
#include "ocamlrandom.h"

int main(int argc, char* argv[]) {
  int n = 10;
  if (argc == 2) n = atoi(argv[1]);

  for (int i = 0; i < n; i++)
    printf("%08x\n", bits());

  return 0;
}

