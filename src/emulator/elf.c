#include "elf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shdr read_elf_header(char *file) {
  FILE *f = fopen(file, "rb");
  if (!f) {
    perror("Failed to open ELF file");
    exit(EXIT_FAILURE);
  }

  struct elfhdr ehdr;
  if (fread(&ehdr, sizeof(ehdr), 1, f) != 1) {
    perror("Failed to read ELF header");
    fclose(f);
    exit(EXIT_FAILURE);
  }

  // Read elf file
  if (ehdr.magic[0] == ELF_MAGIC_0 && ehdr.magic[1] == ELF_MAGIC_1 &&
      ehdr.magic[2] == ELF_MAGIC_2 && ehdr.magic[3] == ELF_MAGIC_3) {
    printf("The file is a valid ELF file.\n");
  } else {
    printf("The file is not a valid ELF file.\n");
  }

  // Seek to Section Header Table
  fseek(f, ehdr.shoff, SEEK_SET);

  // Read all section headers
  struct shdr *sections = malloc(ehdr.shnum * sizeof(struct shdr));
  int i = fread(sections, sizeof(struct shdr), ehdr.shnum, f);

  // Locate the .text section
  char *shstrtab = NULL;
  struct shdr shstrtab_header = sections[ehdr.shstrndx];

  fseek(f, shstrtab_header.offset, SEEK_SET);
  shstrtab = malloc(shstrtab_header.size);
  fread(shstrtab, shstrtab_header.size, 1, f);

  for (int i = 0; i < ehdr.shnum; i++) {
    const char *section_name = shstrtab + sections[i].name;
    if (strcmp(section_name, ".text") == 0) {
      return sections[i];
    }
  }
};
