#include <bbattery.h>
#include "xoshiro256pp.h"


int main() {
  unif01_Gen* gen = create_x256pp(1);
  bbattery_SmallCrush(gen);
  // bbattery_pseudoDIEHARD(gen);
  delete_x256pp(gen);
  return 0;
}

