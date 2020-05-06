#include <string.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/bigarray.h>
#include <caml/custom.h>

#include <util.h>
#include <unif01.h>
#include "unif01_stubs.h"

/* ***************************** [ unif01_Gen ] ***************************** */

void finalize_unif01_Gen_boxed(value bgen) {
  unif01_Gen * gen = unif01_Gen_unbox(bgen);

  gen->state = util_Free(gen->state);
  caml_remove_global_root((value*) &gen->param);
  gen->name = util_Free(gen->name);
  util_Free(gen);

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

/* *************************** [ ExternGenBits ] **************************** */

// We reimplement it ourselves instead of using unif01_CreateExternGenBits. It
// allows us to get rid of the limitation of only one external generator at the
// same time, which allows a more functional interface of the stubs, and to have
// only one finalizer for all the various external generators.

// The principle is the following: TestU01 provides a generic 'unif01_Gen' type.
// This type contains 'GetU01' and 'GetBits' fields that are called to generate
// the bits. Basically, we would like to put, in these fields, a lambda calling
// the given OCaml closure. This is however not possible. We thus leverage the
// fact that 'unif01_Gen' contains also a 'param' field and that this field is
// provided to the functions in 'GetU01' and 'GetBits'. We store the OCaml
// closure in that field. The 'GetU01' and 'GetBits' functions can then be
// written in a static way: they simply take the closure as a parameter and make
// an OCaml call to it.

static unsigned int CGB_BitsInt (void * bits) {
  return Int_val(caml_callback((value) bits, Val_unit)) << 2;
}

static unsigned long CGB_Bits (void * bits, void * junk) {
  return CGB_BitsInt(bits);
}

static double CGB_U01 (void * bits, void * junk) {
  // One must avoid casting the int to a long before the division, because
  // casting to long fills the other bits with 1, and the result will not give a
  // number between 0 and 1. This is why U01 does not depend on Bits but on an
  // additional BitsInt, providing an unsigned int.
  return CGB_BitsInt(bits) / unif01_NORM32;
}

static void WrExternGen (void * junk) {}

value caml_unif01_CreateExternGenBits(value bname, value bbits) {
  CAMLparam2(bname, bbits);
  CAMLlocal1(bgen);
  unif01_Gen * gen;

  gen = util_Malloc(sizeof(unif01_Gen));
  gen->state = NULL;
  caml_register_global_root((value*) &gen->param);
  gen->param = (void*) bbits;
  gen->Write = WrExternGen;
  gen->GetU01 = CGB_U01;
  gen->GetBits = CGB_Bits;

  char * name = Bytes_val(bname);
  size_t len = strlen(name);
  gen->name = util_Calloc(len + 2, sizeof(char));
  strncpy(gen->name, name, len);

  bgen = caml_alloc_custom(&unif01_Gen_boxed, sizeof(unif01_Gen*), 0, 1);
  memcpy(Data_custom_val(bgen), &gen, sizeof(unif01_Gen*));

  CAMLreturn(bgen);
}
