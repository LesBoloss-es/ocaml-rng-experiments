#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>

#include "../reference.h"
#include "../../testutils/testutils.h"

int main(int argc, char* argv[]) {
  return testutils_run(argc, argv, sm64_seed, sm64_next);
}
