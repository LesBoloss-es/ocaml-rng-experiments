#include <string.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/bigarray.h>
#include <caml/custom.h>

#include <unif01.h>

static struct custom_operations unif01_Gen_boxed;

#define unif01_Gen_unbox(bgen) (* (unif01_Gen**) Data_custom_val(bgen))

value caml_unif01_CreateExternGenBits(value name, value bits);

value caml_unif01_CreateExternGenInt32(value name, value bits);

value caml_unif01_CreateExternGen01(value name, value bits);
