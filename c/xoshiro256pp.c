/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>
#include <stdio.h>

/* This is xoshiro256++ 1.0, one of our all-purpose, rock-solid generators.
   It has excellent (sub-ns) speed, a state (256 bits) that is large
   enough for any parallel application, and it passes all tests we are
   aware of.

   For generating just floating-point numbers, xoshiro256+ is even faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t default_state[4] = {
  0xdeadbeefdeadbeef,
  0x4242424242424242,
  0x3737373737373737,
  0xca7aca7aca7aca7a
};

uint64_t next(uint64_t s[4]) {
	const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 45);

	return result;
}

void initialise(uint64_t s[4], int seed) {
  (void)seed; // TODO.
  for (int i = 0; i < 4; i++)
    s[i] = default_state[i];
}

// TestU01 interface

#include <unif01.h>
#include <malloc.h>

unsigned long next_u30_hi(uint64_t s[4]) {
  uint64_t n = next(s);
  return (n >> 34);
}

static void write_state(void *s) {
  printf("[|");
  for (int i = 0; i < 4; i++)
    printf("%lx; ", ((uint64_t*)s)[i]);
}

static double next_double_u01(void *par, void *s) {
  (void)par;
  double r1 = (double)next_u30_hi(s);
  double r2 = (double)next_u30_hi(s);
  return (r1 / 1073741824.0 + r2) / 1073741824.0;
}

static unsigned long next_u01(void *par, void *s) {
  (void)par;
  return next_u30_hi(s);
}

unif01_Gen* create_x256pp(int seed) {
  unif01_Gen* gen;
  uint64_t* state;

  gen = malloc(sizeof(unif01_Gen));
  gen->state = state = malloc(sizeof(uint64_t) * 4);
  initialise(state, seed);
  gen->param = NULL;
  gen->Write = write_state;
  gen->GetU01 = next_double_u01;
  gen->GetBits = next_u01;
  gen->name = "xoshiro256++";

  return gen;
}

void delete_x256pp(unif01_Gen* gen) {
  free(gen->state);
  free(gen);
}

