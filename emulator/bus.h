#ifndef BUS_H
#define BUS_H

#include "types.h"

#define DRAM_SIZE 1 * 1024 * 1204 // 1 GB RAM

typedef struct Bus {
  uint32 dram[DRAM_SIZE];
} Bus;

uint32 bus_read(Bus *bus, uint32 addr, uint32 size);
void bus_write(Bus *bus, uint32 addr, uint32 size, uint32 value);

#endif
