#ifndef CPU_H
#define CPU_H

#define R 0b0110011
#define I 0b0010011
#define L 0b00000011
#define S 0b0100011
#define B 0b11000011

#define ADDSUB 0x0
#define ADD 0x00
#define SUB 0x20
#define SLL 0x1
#define SLT 0x2
#define SLTU 0x3
#define XOR 0x4
#define SRL 0x5
#define SRA 0x20
#define OR 0x6
#define AND 0x7

#define rd(v) (v >> 7) & 0x1f
#define rs1(v) (v >> 15) & 0x1f
#define rs2(v) (v >> 20) & 0x1f

#include "bus.h"

typedef struct CPU {
  uint64 riscv_register[32];
  uint64 pc;
  uint32 csr[4096];
} CPU;

void create_cpu(CPU *cpu);
void run_instruction(CPU *cpu, uint32 instr);
void reset_cpu(CPU *cpu);
void run_r_instructions(CPU *cpu, uint32 instr);
void run_i_instructions(CPU *cpu, uint32 instr);
void run_l_instructions(CPU *cpu, uint32 instr);
void run_s_instructions(CPU *cpu, uint32 instr);
void rin_b_instructions(CPU *cpu, uint32 instr);
uint32 cpu_fetch_instruction(Bus *bus);
#endif