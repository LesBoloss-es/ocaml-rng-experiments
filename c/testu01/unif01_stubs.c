#include <string.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/bigarray.h>
#include <caml/custom.h>

#include <unif01.h>
#include "unif01_stubs.h"

void finalize_unif01_Gen_boxed(value bgen) {
  unif01_Gen * gen = unif01_Gen_unbox(bgen);
  unif01_DeleteExternGenBits(gen);
  return;
}

static struct custom_operations unif01_Gen_boxed = {
 identifier: "unif01_Gen_boxed",
 finalize: finalize_unif01_Gen_boxed,
 compare: custom_compare_default,
 hash: custom_hash_default,
 serialize: custom_serialize_default,
 deserialize: custom_deserialize_default
};

value camlBits_closure;
unsigned int camlBits() {
  return Int_val(caml_callback(camlBits_closure, Val_unit));
}
value caml_unif01_CreateExternGenBits(value name, value bits) {
  CAMLparam2(name, bits);
  CAMLlocal1(bgen);

  camlBits_closure = bits;

  unif01_Gen * gen;
  gen = unif01_CreateExternGenBits(Bytes_val(name), camlBits);

  bgen = caml_alloc_custom(&unif01_Gen_boxed, sizeof(unif01_Gen*), 0, 1);
  memcpy(Data_custom_val(bgen), &gen, sizeof(unif01_Gen*));

  CAMLreturn(bgen);
}

value caml_unif01_DeleteExternGenBits(value bgen) {
  CAMLparam1(bgen);
  finalize_unif01_Gen_boxed(bgen);
  CAMLreturn(Val_unit);
}
