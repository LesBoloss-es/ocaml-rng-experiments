#ifndef TESTUTILS_H
#define TESTUTILS_H 1

#include <stdint.h>
int testutils_run(int, char**, void(*)(uint64_t), uint64_t(*)(void));

#endif
