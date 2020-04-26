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
unif01_Gen unif01_CreateExternGenFromCamlBits(value name, value bits) {
  camlBits_closure = &bits;
  return unif01_CreateExternGenBits(String_val(name), camlBits);
}

/* ***************************** [ SmallCrush ] ***************************** */

value caml_bbattery_SmallCrush(value name, value bits) {
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, bits);
  bbattery_SmallCrush(gen);
  unif01_DeleteExternGenBits(gen);
  return Val_unit;
}

value caml_bbattery_SmallCrushFile(value filename) {
  bbattery_SmallCrushFile(String_val(filename));
  return Val_unit;
}

/* ******************************* [ Crush ] ******************************** */


value caml_bbattery_Crush(value name, value bits) {
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, bits);
  bbattery_Crush(gen);
  unif01_DeleteExternGenBits(gen);
  return Val_unit;
}

/* ****************************** [ BigCrush ] ****************************** */

value caml_bbattery_BigCrush(value name, value bits) {
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, bits);
  bbattery_BigCrush(gen);
  unif01_DeleteExternGenBits(gen);
  return Val_unit;
}

/* ****************************** [ DIEHARD ] ******************************* */

value caml_bbattery_pseudoDIEHARD(value name, value bits) {
  unif01_Gen *gen;
  gen = unif01_CreateExternGenFromCamlBits(name, bits);
  bbattery_pseudoDIEHARD(gen);
  unif01_DeleteExternGenBits(gen);
  return Val_unit;
}
