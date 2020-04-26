#include <unif01.h>
#include <bbattery.h>
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

value * camlBits_closure = NULL;
unsigned int camlBits() {
  return Int_val(caml_callback(*camlBits_closure, Val_unit));
}
unif01_Gen *unif01_CreateExternGenFromCamlBits(value name, value *bits) {
  CAMLparam2(name, *bits);
  if (camlBits_closure == NULL)
    caml_register_global_root(camlBits_closure);
  camlBits_closure = bits;
  return unif01_CreateExternGenBits(Bytes_val(name), camlBits);
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

CAMLprim value caml_bbattery_SmallCrush(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_SmallCrush(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_SmallCrushFile(value filename) {
  CAMLparam1(filename);
  bbattery_SmallCrushFile(Bytes_val(filename));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatSmallCrush(value name, value bits, value rep) {
  CAMLparam3(name, bits, rep);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatSmallCrush(gen, int_array_from_int32_bigarray(rep));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

/* ******************************* [ Crush ] ******************************** */

CAMLprim value caml_bbattery_Crush(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_Crush(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatCrush(value name, value bits, value rep) {
  CAMLparam3(name, bits, rep);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatCrush(gen, int_array_from_int32_bigarray(rep));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

/* ****************************** [ BigCrush ] ****************************** */

CAMLprim value caml_bbattery_BigCrush(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_BigCrush(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatBigCrush(value name, value bits, value rep) {
  CAMLparam3(name, bits, rep);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatBigCrush(gen, int_array_from_int32_bigarray(rep));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

/* ******************************* [ Rabbit ] ******************************* */

CAMLprim value caml_bbattery_Rabbit(value name, value bits, value nb) {
  CAMLparam3(name, bits, nb);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_Rabbit (gen, Double_val(nb));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RabbitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_RabbitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatRabbit(value name, value bits, value nb, value rep) {
  CAMLparam4(name, bits, nb, rep);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatRabbit(gen, Double_val(nb), int_array_from_int32_bigarray(rep));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

/* ****************************** [ Alphabit ] ****************************** */

CAMLprim value caml_bbattery_Alphabit(value name, value bits, value nb, value r, value s) {
  CAMLparam5(name, bits, nb, r, s);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_Alphabit (gen, Double_val(nb), Int_val(r), Int_val(s));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_AlphabitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_AlphabitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatAlphabit(value name, value bits, value nb, value r, value s, value rep) {
  CAMLparam5(name, bits, nb, r, s); CAMLxparam1(rep);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatAlphabit(gen, Double_val(nb), Int_val(r), Int_val(s), int_array_from_int32_bigarray(rep));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}
CAMLprim value camlbytecode_bbattery_RepeatAlphabit(value * argv, int argn) {
  return caml_bbattery_RepeatAlphabit(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value caml_bbattery_BlockAlphabit(value name, value bits, value nb, value r, value s) {
  CAMLparam5(name, bits, nb, r, s);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_BlockAlphabit (gen, Double_val(nb), Int_val(r), Int_val(s));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_BlockAlphabitFile(value filename, value nb) {
  CAMLparam2(filename, nb);
  bbattery_BlockAlphabitFile (Bytes_val(filename), Double_val(nb));
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_RepeatBlockAlphabit(value name, value bits, value nb, value r, value s, value rep, value w) {
  CAMLparam5(name, bits, nb, r, s); CAMLxparam2(rep, w);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_RepeatBlockAlphabit(gen, Double_val(nb), Int_val(r), Int_val(s), int_array_from_int32_bigarray(rep), Int_val(w));
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}
CAMLprim value camlbytecode_bbattery_RepeatBlockAlphabit(value * argv, int argn) {
  return caml_bbattery_RepeatBlockAlphabit(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

/* ****************************** [ DIEHARD ] ******************************* */

CAMLprim value caml_bbattery_pseudoDIEHARD(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_pseudoDIEHARD(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

/* **************************** [ FISP 140 2 ] ****************************** */

CAMLprim value caml_bbattery_FIPS_140_2(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_FIPS_140_2(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}

CAMLprim value caml_bbattery_FIPS_140_2File(value filename) {
  CAMLparam1(filename);
  bbattery_FIPS_140_2File(Bytes_val(filename));
  CAMLreturn(Val_unit);
}
