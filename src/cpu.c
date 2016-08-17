#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "opcodes.h"

unsigned char font[FNT_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

int cpu_timer_reset(chip8_t *chip8)
{
	if(chip8->delay_timer > 0)
	{
		chip8->delay_timer--;
	}

	if(chip8->sound_timer > 0)
	{
		chip8->sound_timer--;

		if(chip8->sound_timer == 0)
		{
			//beep
		}
	}

	return 0;
}

int cpu_init_reset(chip8_t *chip8)
{
	unsigned int i;

	// reset arrays
	memset(chip8->memory, 0, sizeof(chip8->memory));
	memset(chip8->graphics, 0, sizeof(chip8->graphics));
	memset(chip8->V, 0, sizeof(chip8->V));
	memset(chip8->_stack, 0, sizeof(chip8->_stack));
	memset(chip8->keys, 0, sizeof(chip8->keys));

	// reset pointers, indexes, pc and opcode
	chip8->I = 0;
	chip8->pc = 0x200;
	chip8->sp = 0;
	chip8->opcode = 0;

	// reset timers
	chip8->delay_timer = 0;
	chip8->sound_timer = 0;

	// debug flag
	chip8->debug_flag = 0;

	// load fontset
	for(i = 0; i < FNT_SIZE; i++)
	{
		chip8->memory[i] = font[i];
	}

	return 0;
}

int cpu_cycle(chip8_t *chip8)
{
	chip8->opcode = (chip8->memory[chip8->pc] << 8 |
			chip8->memory[chip8->pc + 1]);

	cpu_timer_reset(chip8);

	switch(chip8->opcode & 0xF000)
	{
		case 0x0000:
			switch(chip8->opcode & 0x00FF)
			{
				case 0x00E0:
					_00E0(chip8);
					break;
				case 0x00EE:
					_00EE(chip8);
					break;
				default:
					chip8->pc += 2;
					printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
			}
			break;
		case 0x1000:
			_1NNN(chip8);
			break;
		case 0x2000:
			_2NNN(chip8);
			break;
		case 0x3000:
			_3XNN(chip8);
			break;
		case 0x4000:
			_4XNN(chip8);
			break;
		case 0x5000:
			_5XY0(chip8);
		case 0x6000:
			_6XNN(chip8);
			break;
		case 0x7000:
			_7XNN(chip8);
			break;
		case 0x8000:
			switch(chip8->opcode & 0x000F)
			{
				case 0x0:
					_8XY0(chip8);
					break;
				case 0x1:
					_8XY1(chip8);
					break;
				case 0x2:
					_8XY2(chip8);
					break;
				case 0x3:
					_8XY3(chip8);
					break;
				case 0x4:
					_8XY4(chip8);
					break;
				case 0x5:
					_8XY5(chip8);
					break;
				case 0x6:
					_8XY6(chip8);
					break;
				case 0x7:
					_8XY7(chip8);
					break;
				case 0xE:
					_8XYE(chip8);
					break;
				default:
					chip8->pc += 2;
					printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
			}
			break;
		case 0x9000:
			switch(chip8->opcode & 0x000F)
			{
				case 0x0:
					_9XY0(chip8);
					break;
				default:
					chip8->pc += 2;
					printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
			}
			break;
		case 0xA000:
			_ANNN(chip8);
			break;
		case 0xB000:
			_BNNN(chip8);
			break;
		case 0xC000:
			_CXNN(chip8);
			break;
		case 0xD000:
			_DXYN(chip8);
			break;
		case 0xE000:
			switch(chip8->opcode & 0x00FF)
			{
				case 0x9E:
					_EX9E(chip8);
					break;
				case 0xA1:
					_EXA1(chip8);
					break;
				default:
					chip8->pc += 2;
					printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
			}
			break;
		case 0xF000:
			switch(chip8->opcode & 0x00FF)
			{
				case 0x07:
					_FX07(chip8);
					break;
				case 0x0A:
					_FX0A(chip8);
					break;
				case 0x15:
					_FX15(chip8);
					break;
				case 0x18:
					_FX18(chip8);
					break;
				case 0x1E:
					_FX1E(chip8);
					break;
				case 0x29:
					_FX29(chip8);
					break;
				case 0x33:
					_FX33(chip8);
					break;
				case 0x55:
					_FX55(chip8);
					break;
				case 0x65:
					_FX65(chip8);
					break;
				default:
					chip8->pc += 2;
					printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
			}
			break;
		default:
			chip8->pc += 2;
			printf("[WRNG] - Invalid opcode: %4X\n", chip8->opcode);
	}

	return 0;
}
