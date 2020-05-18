// Reference:  http://prng.di.unimi.it/xoshiro256plusplus.c

#include <stdint.h>

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static uint64_t x256pp_state[4] = {
  0xd430ebc2f4d9e7b8,
  0x44815975ddd19d52,
  0xbb18c2b0b18d0bfe,
  0x6c0681407295c644
};

uint64_t x256pp_next(void) {
	const uint64_t result = rotl(x256pp_state[0] + x256pp_state[3], 23) + x256pp_state[0];

	const uint64_t t = x256pp_state[1] << 17;

	x256pp_state[2] ^= x256pp_state[0];
	x256pp_state[3] ^= x256pp_state[1];
	x256pp_state[1] ^= x256pp_state[2];
	x256pp_state[0] ^= x256pp_state[3];

	x256pp_state[2] ^= t;

	x256pp_state[3] = rotl(x256pp_state[3], 45);

	return result;
}

static uint64_t sm64_next_stateless(uint64_t* s) {
	uint64_t z = (*s += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void x256pp_seed(uint64_t seed) {
  uint64_t s = seed;
  for (int i = 0; i < 4; i++)
    x256pp_state[i] = sm64_next_stateless(&s);
}

