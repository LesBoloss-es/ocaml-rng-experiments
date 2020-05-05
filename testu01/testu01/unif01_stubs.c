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

static unsigned int EGB_CamlBits (void * bits) {
  return Int_val(caml_callback((value) bits, Val_unit)) << 2;
}

static unsigned long EGB_Bits (void * bits, void * junk) {
  return EGB_CamlBits(bits);
}

static double EGB_U01 (void * bits, void * junk) {
  // one must avoid casting the int to a long before the division, because
  // casting to long fills the other bits with 1, and the result will not give a
  // number between 0 and 1.
  return EGB_CamlBits(bits) / unif01_NORM32;
}

static void WrExternGen (void * junk) {}

value caml_unif01_CreateExternGenBits(value bname, value bbits) {
  CAMLparam2(bname, bbits);
  CAMLlocal1(bgen);
  unif01_Gen * gen;

  gen = util_Malloc(sizeof(unif01_Gen));
  gen->state = NULL;
  gen->param = (void*) bbits;
  gen->Write = WrExternGen;
  gen->GetU01 = EGB_U01;
  gen->GetBits = EGB_Bits;

  char * name = Bytes_val(bname);
  size_t len = strlen(name);
  gen->name = util_Calloc(len + 2, sizeof(char));
  strncpy(gen->name, name, len);

  bgen = caml_alloc_custom(&unif01_Gen_boxed, sizeof(unif01_Gen*), 0, 1);
  memcpy(Data_custom_val(bgen), &gen, sizeof(unif01_Gen*));

  CAMLreturn(bgen);
}