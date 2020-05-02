#include <string.h>

#include <unif01.h>
#include <bbattery.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/bigarray.h>
#include <caml/custom.h>

static struct custom_operations unif01_Gen_boxed = {
 identifier  : "unif01_Gen_boxed",
 finalize    : custom_finalize_default,
 compare     : custom_compare_default,
 hash        : custom_hash_default,
 serialize   : custom_serialize_default,
 deserialize : custom_deserialize_default
};

#define unif01_Gen_unbox(bgen) (* (unif01_Gen**) Data_custom_val(bgen))

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
  unif01_Gen * gen = unif01_Gen_unbox(bgen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

int * int_array_from_int32_bigarray(value ba) {
  CAMLparam1(ba);
  int ba32_length = Caml_ba_array_val(ba)->dim[0];
  int32_t * ba32 = Caml_ba_data_val(ba);
  int * a = malloc(ba32_length * sizeof(int));
  for (int i = 0 ; i < ba32_length ; i++) {
    a[i] = (int) ba32[i];
  };
  return a;
}

/* ***************************** [ SmallCrush ] ***************************** */

CAMLprim value caml_bbattery_SmallCrush(value bgen) {
  CAMLparam1(bgen);
  unif01_Gen * gen = unif01_Gen_unbox(bgen);
  bbattery_SmallCrush(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_SmallCrushFile(value filename) {
  CAMLparam1(filename);
  bbattery_SmallCrushFile(Bytes_val(filename));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatSmallCrush(value bgen, value rep) {
  CAMLparam2(bgen, rep);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatSmallCrush(gen, int_array_from_int32_bigarray(rep));
  CAMLreturn(Val_unit);
}

/* ******************************* [ Crush ] ******************************** */

CAMLprim value caml_bbattery_Crush(value bgen) {
  CAMLparam1(bgen);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_Crush(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatCrush(value bgen, value rep) {
  CAMLparam2(bgen, rep);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatCrush(gen, int_array_from_int32_bigarray(rep));
  CAMLreturn(Val_unit);
}

/* ****************************** [ BigCrush ] ****************************** */

CAMLprim value caml_bbattery_BigCrush(value bgen) {
  CAMLparam1(bgen);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_BigCrush(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatBigCrush(value bgen, value rep) {
  CAMLparam2(bgen, rep);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatBigCrush(gen, int_array_from_int32_bigarray(rep));
  CAMLreturn(Val_unit);
}

/* ******************************* [ Rabbit ] ******************************* */

CAMLprim value caml_bbattery_Rabbit(value bgen, value nb) {
  CAMLparam2(bgen, nb);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_Rabbit (gen, Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RabbitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_RabbitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatRabbit(value bgen, value nb, value rep) {
  CAMLparam3(bgen, nb, rep);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatRabbit(gen, Double_val(nb), int_array_from_int32_bigarray(rep));
  CAMLreturn(Val_unit);
}

/* ****************************** [ Alphabit ] ****************************** */

CAMLprim value caml_bbattery_Alphabit(value bgen, value nb, value r, value s) {
  CAMLparam4(bgen, nb, r, s);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_Alphabit (gen, Double_val(nb), Int_val(r), Int_val(s));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_AlphabitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_AlphabitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatAlphabit(value bgen, value nb, value r, value s, value rep) {
  CAMLparam5(bgen, nb, r, s, rep);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatAlphabit(gen, Double_val(nb), Int_val(r), Int_val(s), int_array_from_int32_bigarray(rep));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_BlockAlphabit(value bgen, value nb, value r, value s) {
  CAMLparam4(bgen, nb, r, s);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_BlockAlphabit (gen, Double_val(nb), Int_val(r), Int_val(s));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_BlockAlphabitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_BlockAlphabitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatBlockAlphabit(value bgen, value nb, value r, value s, value rep, value w) {
  CAMLparam5(bgen, nb, r, s, rep); CAMLxparam1(w);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_RepeatBlockAlphabit(gen, Double_val(nb), Int_val(r), Int_val(s), int_array_from_int32_bigarray(rep), Int_val(w));
  CAMLreturn(Val_unit);
}
CAMLprim value camlbytecode_bbattery_RepeatBlockAlphabit(value * argv, int argn) {
  return caml_bbattery_RepeatBlockAlphabit(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

/* ****************************** [ DIEHARD ] ******************************* */

CAMLprim value caml_bbattery_pseudoDIEHARD(value bgen) {
  CAMLparam1(bgen);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_pseudoDIEHARD(gen);
  CAMLreturn(Val_unit);
}

/* **************************** [ FISP 140 2 ] ****************************** */

CAMLprim value caml_bbattery_FIPS_140_2(value bgen) {
  CAMLparam1(bgen);
  unif01_Gen *gen = unif01_Gen_unbox(bgen);
  bbattery_FIPS_140_2(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_FIPS_140_2File(value filename) {
  CAMLparam1(filename);
  bbattery_FIPS_140_2File(Bytes_val(filename));
  CAMLreturn(Val_unit);
}
