#ifndef SPLITMIX64_H
#define SPLITMIX64_H

#include <stdint.h>

uint64_t sm64_next_stateless(uint64_t*);

void sm64_seed(uint64_t);
uint64_t sm64_next();

#endif

