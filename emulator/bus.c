#include "bus.h"

uint32 bus_read(Bus *bus, uint32 addr, uint32 size) { return bus->dram[addr]; };

void bus_write(Bus *bus, uint32 addr, uint32 size, uint32 value) {
  bus->dram[addr] = value;
};
