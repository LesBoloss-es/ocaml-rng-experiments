#include "ocamlrandom.h"
#include <malloc.h>
#include <unif01.h>

// Simple interface

ocaml_state default_state = {
  .buf = {
    0x3ae2522b, 0x1d8d4634, 0x15b4fad0, 0x18b14ace, 0x12f8a3c4, 0x3b086c47,
    0x16d467d6, 0x101d91c7, 0x321df177, 0x0176c193, 0x1ff72bf1, 0x1e889109,
    0x0b464b18, 0x2b86b97c, 0x0891da48, 0x03137463, 0x085ac5a1, 0x15d61f2f,
    0x3bced359, 0x29c1c132, 0x3a86766e, 0x366d8c86, 0x1f5b6222, 0x3ce1b59f,
    0x2ebf78e1, 0x27cd1b86, 0x258f3dc3, 0x389a8194, 0x02e4c44c, 0x18c43f7d,
    0x0f6e534f, 0x1e7df359, 0x055d0b7e, 0x10e84e7e, 0x126198e4, 0x0e7722cb,
    0x1cbede28, 0x3391b964, 0x3d40e92a, 0x0c59933d, 0x0b8cd0b7, 0x24efff1c,
    0x2803fdaa, 0x08ebc72e, 0x0f522e32, 0x05398edc, 0x2144a04c, 0x0aef3cbd,
    0x01ad4719, 0x35b93cd6, 0x2a559d4f, 0x1e6fd768, 0x26e27f36, 0x186f18c3,
    0x2fbf967a,
  },
  .idx = 0
};

static void initialise(ocaml_state* s, int seed) {
  (void)seed; //TODO
  (void)s; // TODO
  for (int i = 0; i < 55; i++)
    s->buf[i] = default_state.buf[i];
  s->idx = 0;
}

unsigned long next(ocaml_state* s) {
  s->idx = (s->idx + 1) % 55;
  int curval = s->buf[s->idx];
  int newval = s->buf[(s->idx + 24) % 55] + (curval ^ ((curval >> 25) & 0x1F));
  int newval30 = newval & 0x3FFFFFFF;
  s->buf[s->idx] = newval30;
  return newval30;
}

double next_double(ocaml_state* s) {
  double r1 = (double)next(s);
  double r2 = (double)next(s);
  return (r1 / 1073741824.0 + r2) / 1073741824.0;
}

// TestU01 interface

static void write_ocamlrandom(void *s) {
  printf("[|");
  for (int i = 0; i < 55; i++)
    printf("%d; ", ((ocaml_state*)s)->buf[i]);
  printf("|] @ %d", ((ocaml_state*)s)->idx);
}

static double next_double_u01(void *par, void *s) {
  (void)par;
  return next_double(s);
}

static unsigned long next_u01(void *par, void *s) {
  (void)par;
  // Equivalent to OCaml's [Random.int64 (2^32 + 1)]
  return next(s) | ((next(s) & 3) << 30) ;
}

unif01_Gen* create_ocamlrandom(int seed) {
  unif01_Gen* gen;
  ocaml_state* state;

  gen = malloc(sizeof(unif01_Gen));
  gen->state = state = malloc(sizeof(ocaml_state));
  initialise(state, seed);
  gen->param = NULL;
  gen->Write = write_ocamlrandom;
  gen->GetU01 = next_double_u01;
  gen->GetBits = next_u01;
  gen->name = "ocamlrandom";

  return gen;
}

void delete_ocamlrandom(unif01_Gen* gen) {
  free(gen->state);
  free(gen);
}

