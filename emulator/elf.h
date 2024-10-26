#ifndef ELF_H
#define ELF_H

#include "types.h"
#define ELF_MAGIC 0x464C457FU // "\x7FELF" in little endian

// File header
struct elfhdr {
  uint8 magic; // must equal ELF_MAGIC
  uint8 elf[12];
  uint8 type;
  uint8 machine;
  uint8 version;
  uint64 entry;
  uint64 phoff;
  uint64 shoff;
  uint8 flags;
  uint8 ehsize;
  uint8 phentsize;
  uint8 phnum;
  uint8 shentsize;
  uint8 shnum;
  uint8 shstrndx;
};

// Program section header
struct proghdr {
  uint32 type;
  uint32 flags;
  uint64 off;
  uint64 vaddr;
  uint64 paddr;
  uint64 filesz;
  uint64 memsz;
  uint64 align;
};

// Values for Proghdr type
#define ELF_PROG_LOAD 1

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC 1
#define ELF_PROG_FLAG_WRITE 2
#define ELF_PROG_FLAG_READ 4

void read_elf_header32(struct elfhdr *elf);
#endif
