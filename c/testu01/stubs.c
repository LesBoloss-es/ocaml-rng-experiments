#include <unif01.h>
#include <bbattery.h>
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>

value * camlBits_closure = NULL;
unsigned int camlBits() {
  return Int_val(caml_callback(*camlBits_closure, Val_unit));
}
unif01_Gen *unif01_CreateExternGenFromCamlBits(value name, value *bits) {
  camlBits_closure = bits;
  return unif01_CreateExternGenBits(Bytes_val(name), camlBits);
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

/* ******************************* [ Crush ] ******************************** */

CAMLprim value caml_bbattery_Crush(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_Crush(gen);
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

/* ****************************** [ DIEHARD ] ******************************* */

CAMLprim value caml_bbattery_pseudoDIEHARD(value name, value bits) {
  CAMLparam2(name, bits);
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, &bits);
  bbattery_pseudoDIEHARD(gen);
  unif01_DeleteExternGenBits(gen);
  CAMLreturn(Val_unit);
}
