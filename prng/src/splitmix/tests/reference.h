#ifndef SPLITMIX64_H
#define SPLITMIX64_H 1

#include <stdint.h>

uint64_t next();
void seed(uint64_t);

#endif
