#ifndef __CPU_H_
#define __CPU_H_

#include <SDL/SDL.h>

#define MEM_SIZE 4096
#define GFX_SIZE 2048

#define REG_SIZE 16
#define STK_SIZE 16

#define KEY_SIZE 16

#define FNT_SIZE 80

typedef struct
{
	//memory
	unsigned char memory[MEM_SIZE];
	//graphic memory
	unsigned char graphics[GFX_SIZE];

	// registers 0-15
	unsigned char V[REG_SIZE];

	// index register
	unsigned short I;
	// program counter
	unsigned short pc;

	// stack 0-15
	unsigned short _stack[STK_SIZE];
	// stack pointer
	unsigned short sp;

	// op code
	unsigned short opcode;

	// keypad 0-15
	unsigned char keys[KEY_SIZE];

	// timers
	unsigned char delay_timer;
	unsigned char sound_timer;

	// flags
	unsigned short draw_flag : 1;

	unsigned short int debug_flag : 1;

} chip8_t;

int cpu_timer_reset(chip8_t *chiip8);
int cpu_init_reset(chip8_t *chip8);
int cpu_cycle(chip8_t *chip8);

#endif
