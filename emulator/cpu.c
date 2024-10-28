#include "cpu.h"
#include "bus.h"
#include "types.h"
#include <stdio.h>

void initialize_registers(uint32 *reg) {}

void create_cpu(CPU *cpu) {
  for (int i = 0; i < 32; i++) {
    cpu->riscv_register[i] = 0;
  }
  cpu->pc = DRAM_BASE;

  for (int i = 0; i < 4096; i++) {
    cpu->csr[i] = 0;
  }
};

void reset_cpu(CPU *cpu) { create_cpu(cpu); }

void run_r_instructions(CPU *cpu, uint32 instr) {
  int func3 = (instr >> 12) & 0x7;  // func3 (3 bits)
  int func7 = (instr >> 25) & 0x7f; // func7 (7 bits)
  int rd = rd(instr);
  int rs1 = rs1(instr);
  int rs2 = rs2(instr);
  uint64 *regs = cpu->riscv_register;
  switch (func3) {
  case ADDSUB:
    switch (func7) {
    case ADD:
      regs[rd] = regs[rs1] + regs[rs2];
      break;
    case SUB:
      regs[rd] = regs[rs1] - regs[rs2];
      break;
    }
    break;

  case SLL:
    regs[rd] = regs[rs1] << regs[rs2];
    break;

  case SLT:
    regs[rd] = (regs[rs1] < regs[rs2]) ? 1 : 0; // Set Less Than
    break;

  case SLTU:
    regs[rd] = (regs[rs1] < regs[rs2]) ? 1 : 0; // Set Less Than Unsigned
    break;

  case XOR:
    regs[rd] = regs[rs1] ^ regs[rs2];
    break;

  case SRL:
    if (func7 == SRL) {
      regs[rd] = regs[rs1] >> regs[rs2]; // Shift Right Logical
    } else if (func7 == SRA) {
      regs[rd] = (int)regs[rs1] >> regs[rs2]; // Shift Right Arithmetic
    }
    break;

  case OR:
    regs[rd] = regs[rs1] | regs[rs2];
    break;

  case AND:
    regs[rd] = regs[rs1] & regs[rs2];
    break;

  default:
    break;
  }
}

void run_i_instructions(CPU *cpu, uint32 instr) {
  int func3 = (instr >> 12) & 0x7; // func3 (3 bits)

  int rd = rd(instr);
  int rs1 = rs1(instr);

  int32 imm = (int32)(instr >> 20); // Extract imm[11:0] (12 bits)
  if (imm & 0x800) {                // If the sign bit (bit 11) is set,
    imm |= 0xFFFFF000;              // sign-extend to 32 bits
  }

  uint64 *regs = cpu->riscv_register;
  switch (func3) {
  case ADD:
    regs[rd] = regs[rs1] + imm;
    break;
  case XOR:
    regs[rd] = regs[rs1] ^ imm;
    break;
  case OR:
    regs[rd] = regs[rs1] | (imm & 0x1F);
    break;
  case AND:
    regs[rd] = regs[rs1] & imm;
    break;
  case SLL:
    regs[rd] = regs[rs1] << (imm & 0x1F);
    break;
  case SRL:
    if ((imm >> 10) & 1) { // SRAI: Shift right arithmetic immediate
      regs[rd] = (int32)regs[rs1] >> (imm & 0x1F); // Sign-extend shift
    } else { // SRLI: Shift right logical immediate
      regs[rd] = (uint32)regs[rs1] >> (imm & 0x1F); // Zero-extend shift
    }
    break;

  case SRA:
    break;

  case SLT:
    regs[rd] = regs[rs1] < imm ? 1 : 0;
    break;
  case SLTU:
    regs[rd] = regs[rs1] < (uint32)imm ? 1 : 0;
    break;
  default:
    break;
  }
}

void run_instruction(CPU *cpu, uint32 instr) {
  int opcode = instr & 0x7f;

  switch (opcode) {
  case R:
    run_r_instructions(cpu, instr);
    break;
  case I:
    run_i_instructions(cpu, instr);
    break;
  case L:

    break;
  case S:
    break;
  case B:
    break;
  default:
    printf("Illegal instruction!!!\n");
    break;
  }
}

uint32 cpu_fetch_instruction(Bus *bus) { return 0; }
