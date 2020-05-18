#ifndef SPLITMIX64_H
#define SPLITMIX64_H 1

#include <stdint.h>

void sm64_seed(uint64_t);
uint64_t sm64_next();

#endif
