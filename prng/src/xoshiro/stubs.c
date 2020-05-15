#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <stdint.h>
#include "reference.h"

value caml_x256pp_seed(value seed) {
  CAMLparam1(seed);
  int64_t x = Int64_val(seed);
  // reinterpret x as an unsigned integer
  x256pp_seed(*(uint64_t*)(&x));
  CAMLreturn(Val_unit);
}

value caml_x256pp_next(value unit) {
  CAMLparam1(unit);
  uint64_t x = x256pp_next();
  // reinterpret x as a signed integer
  value res = caml_copy_int64(*(int64_t*)(&x));
  CAMLreturn(res);
}

value caml_x256pp_bits(value unit) {
  CAMLparam1(unit);
  intnat res = x256pp_next() >> 34;
  CAMLreturn(Val_long(res));
}

value caml_x256pp_bits62(value unit) {
  CAMLparam1(unit);
  long res = x256pp_next() >> 2;
  CAMLreturn(Val_long(res));
}

value caml_x256pp_double(value f) {
  CAMLparam1(f);
  double res = (x256pp_next() >> 11) * 0x1.0p-53;
  res *= Double_val(f);
  CAMLreturn(caml_copy_double(res));
}

