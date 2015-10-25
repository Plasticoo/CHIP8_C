#ifndef __ROM_H_
#define __ROM_H_

#include "cpu.h"

int rom_size(FILE* rom_name);
int rom_load(chip8_t *chip8, char *rom_name);

#endif
