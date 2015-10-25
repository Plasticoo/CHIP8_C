#include <stdio.h>

#include "cpu.h"
#include "memory.h"

void memory_print_emu_info(chip8_t *chip8)
{
	unsigned int i;

	printf("[INFO] - I: %04X\n", chip8->I);
	printf("[INFO] - PC: %04X\n", chip8->pc);
	printf("[INFO] - SP: %d\n", chip8->sp);
	printf("[INFO] - Delay Timer: %d\n", chip8->delay_timer);
	printf("[INFO] - Sound Timer: %d\n", chip8->sound_timer);
	printf("[INFO] - Draw Flag: %d\n", chip8->draw_flag);
	printf("[INFO] - Debug Flag: %d\n", chip8->debug_flag);
	printf("[INFO] - Opcode: %04X\n", chip8->opcode);
	for(i = 0; i < REG_SIZE; i++)
	{
		printf("[INFO] - V[%X]: %02X\n", i, chip8->V[i]);
	}
	
	for(i = 0; i < STK_SIZE; i++)
	{
		printf("[INFO] - Stack[%X]: %02X\n", i, chip8->V[i]);
	}
}

void memory_print_map(chip8_t *chip8)
{
	unsigned int i;

	for(i = 0; i < MEM_SIZE; i++)
	{
		if(i == 0)
		{
			printf("\n0x%3X - %02X ", i, chip8->memory[i]);
		}
		else if(i >= 32 && i % 32 == 0)
		{
			printf("\n0x%3X - %02X ", i, chip8->memory[i]);
		}
		else
		{
			printf("%02X ", chip8->memory[i]);
		}
	}

	putchar('\n');
}
