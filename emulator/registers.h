#include "types.h"
// Define the RISC-V 32-bit register file structure without arrays

typedef struct Register {
  uint32 x0;  // Zero register (always 0)
  uint32 x1;  // Return address (ra)
  uint32 x2;  // Stack pointer (sp)
  uint32 x3;  // Global pointer (gp)
  uint32 x4;  // Thread pointer (tp)
  uint32 x5;  // Temporary/alternate link register (t0)
  uint32 x6;  // Temporary register (t1)
  uint32 x7;  // Temporary register (t2)
  uint32 x8;  // Saved register/frame pointer (s0/fp)
  uint32 x9;  // Saved register (s1)
  uint32 x10; // Function argument/return value (a0)
  uint32 x11; // Function argument/return value (a1)
  uint32 x12; // Function argument (a2)
  uint32 x13; // Function argument (a3)
  uint32 x14; // Function argument (a4)
  uint32 x15; // Function argument (a5)
  uint32 x16; // Function argument (a6)
  uint32 x17; // Function argument (a7)
  uint32 x18; // Saved register (s2)
  uint32 x19; // Saved register (s3)
  uint32 x20; // Saved register (s4)
  uint32 x21; // Saved register (s5)
  uint32 x22; // Saved register (s6)
  uint32 x23; // Saved register (s7)
  uint32 x24; // Saved register (s8)
  uint32 x25; // Saved register (s9)
  uint32 x26; // Saved register (s10)
  uint32 x27; // Saved register (s11)
  uint32 x28; // Temporary register (t3)
  uint32 x29; // Temporary register (t4)
  uint32 x30; // Temporary register (t5)
  uint32 x31; // Temporary register (t6)
} Register;

typedef struct CPU {
  struct Register registers;
  uint32 pc;
  uint32 csr[4096];
} CPU;

void cpu_init(struct CPU *cpu);
uint32 cpu_fetch(struct CPU *cpu);

void dump_registers(struct CPU *cpu);
