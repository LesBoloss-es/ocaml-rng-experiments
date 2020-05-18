// Reference: http://prng.di.unimi.it/splitmix64.c

#include <stdint.h>

static uint64_t s; /* The state can be seeded with any value. */

void sm64_seed(uint64_t seed) {
  s = seed;
}

uint64_t sm64_next() {
	uint64_t z = (s += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}
