#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <stdint.h>
#include "reference.h"

CAMLprim value caml_x256pp_seed(value seed) {
  CAMLparam1(seed);
  int64_t x = Int64_val(seed);
  // reinterpret x as an unsigned integer
  x256pp_seed(*(uint64_t*)(&x));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_x256pp_next(value unit) {
  CAMLparam1(unit);
  uint64_t x = x256pp_next();
  // reinterpret x as a signed integer
  value res = caml_copy_int64(*(int64_t*)(&x));
  CAMLreturn(res);
}

