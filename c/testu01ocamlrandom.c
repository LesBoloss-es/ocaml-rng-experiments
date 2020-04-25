#include <bbattery.h>
#include "ocamlrandom.h"


int main() {
  unif01_Gen* gen = create_ocamlrandom(1);
  // bbattery_SmallCrush(gen);
  bbattery_pseudoDIEHARD(gen);
  delete_ocamlrandom(gen);
  return 0;
}

