#include <unif01.h>
#include <bbattery.h>
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>

value * caml_bits_closure = NULL;

unsigned int bits() {
  return Int_val(caml_callback(*caml_bits_closure, Val_unit));
}

value caml_bbattery_SmallCrush(value name, value bits_closure) {
  caml_bits_closure = &bits_closure;

  unif01_Gen *gen;
  gen = unif01_CreateExternGenBits(String_val(name), bits);
  bbattery_SmallCrush(gen);
  unif01_DeleteExternGenBits(gen);

  return Val_unit;
}

value call_caml_f_ex(value closure, value arg)
{
  CAMLparam2(closure, arg);
  CAMLlocal2(res, tmp);
  res = caml_callback(closure, arg);
  CAMLreturn (res);
}
