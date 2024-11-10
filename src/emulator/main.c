#include "cpu.h"
#include "elf.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void read_text_section(const char *filename, size_t offset, size_t size) {}

int main() {
  CPU cpu;
  Bus bus;

  cpu.bus = &bus;

  int quit = 0;
  char *filename = "test/test.O";
  struct shdr text = read_elf_header("test/test.O");
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Failed to open file");
    exit(1);
  }

  // Move to the `.text` section offset
  fseek(file, text.offset, SEEK_SET);

  // Allocate memory to hold the `.text` section
  uint8 *text_section = malloc(text.size + 4);
  if (!text_section) {
    perror("Failed to allocate memory");
    fclose(file);
    exit(1);
  }

  // Read the `.text` section into memory
  fread(text_section, 1, text.size + 4, file);
  fclose(file);

  // Display instructions as hex (or process them as needed)
  for (size_t i = 0; i < text.size; i += 4) {
    uint32 instruction = *(uint32 *)(text_section + i);
    run_instruction(&cpu, instruction);

    for (int i = 0; i < 32; i++) {
      printf("%d ", (int)cpu.riscv_register[i]);
    }

    printf("\n");
  }

  free(text_section);
  return 0;
}
