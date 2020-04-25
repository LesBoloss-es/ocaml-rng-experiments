#ifndef XOSHIRO256PP_H
#define XOSHIRO256PP_H 1

#include <stdint.h>
#include <unif01.h>

uint64_t next();

unif01_Gen* create_x256pp(int);
void delete_x256pp(unif01_Gen*);

#endif
