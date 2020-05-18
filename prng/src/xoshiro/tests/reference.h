#ifndef XOSHIRO256PP_H
#define XOSHIRO256PP_H 1

#include <stdint.h>

uint64_t x256pp_next();
void x256pp_seed(uint64_t);

#endif

