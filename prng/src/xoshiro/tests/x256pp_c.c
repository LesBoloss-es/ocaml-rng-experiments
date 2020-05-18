#include "reference.h"
#include "../../testutils/testutils.h"

int main(int argc, char* argv[]) {
  return testutils_run(argc, argv, x256pp_seed, x256pp_next);
}
