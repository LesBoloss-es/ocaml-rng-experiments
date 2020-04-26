#ifndef X256PP_H
#define X256PP_H 1

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/alloc.h>

CAMLprim value x256pp_bits();
CAMLprim value x256pp_bits62();
CAMLprim value x256pp_double(value);

#endif
