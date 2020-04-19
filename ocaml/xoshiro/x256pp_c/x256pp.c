#include "x256pp.h"
#include <stdint.h>
#include <stdio.h>

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static uint64_t s[4] = {
  0xdeadbeefdeadbeef,
  0x4242424242424242,
  0x3737373737373737,
  0xca7aca7aca7aca7a
};

static uint64_t next(void) {
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

static long int buf = 0;
static int buf_len = 0;
static const uint64_t mask30 = (1 << 30) - 1;

CAMLprim value x256pp_bits() {
  if (buf_len == 0) {
    buf = next();
    buf_len = 2;
  }
  long int res = buf & mask30;
  buf_len--;
  buf = buf >> 32;
  return Val_long(res);
}
