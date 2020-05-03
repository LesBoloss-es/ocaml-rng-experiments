#include <string.h>

#include <gofw.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>

value caml_gofw_setSuspectp(value suspectp) {
  CAMLparam1(suspectp);
  gofw_Suspectp = Double_val(suspectp);
  CAMLreturn(Val_unit);
}
