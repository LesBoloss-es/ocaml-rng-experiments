#include "reference.h" // seed, next
#include "../../testutils/testutils.h" // testutils_run

int main(int argc, char* argv[]) {
  return testutils_run(argc, argv, seed, next);
}
