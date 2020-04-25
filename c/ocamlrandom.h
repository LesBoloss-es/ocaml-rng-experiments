#ifndef OCAMLRANDOM_H
#define OCAMLRANDOM_H 1

#include <unif01.h>

typedef struct {
  int buf[55];
  int idx;
} ocaml_state;

ocaml_state default_state;
unsigned long next(ocaml_state*);

unif01_Gen* create_ocamlrandom(int seed);
void delete_ocamlrandom(unif01_Gen* gen);

#endif
