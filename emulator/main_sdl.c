#include "bus.h"
#include "cpu.h"
#include "types.h"

int main2() {

  CPU cpu;
  Bus bus;

  create_cpu(&cpu);
  reset_cpu(&cpu);
  int quit = 0;

  while (!quit) {
  };
};
