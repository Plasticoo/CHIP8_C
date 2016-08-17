#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>

#include "cpu.h"

const unsigned int _sdl_keymap[16] =
{
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_4,
	SDLK_q,
	SDLK_w,
	SDLK_e,
	SDLK_r,
	SDLK_a,
	SDLK_s,
	SDLK_d,
	SDLK_f,
	SDLK_z,
	SDLK_x,
	SDLK_c,
	SDLK_v
};

// TODO 0NNN

// store number NN in register VX
void _6XNN(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _NN = (chip8->opcode & 0x00FF);

	chip8->V[_X] = _NN;

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD V%X, %02X\n", _X, _NN);
	}
}

// store the value of register VY in register VX
void _8XY0(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	chip8->V[_X] = chip8->V[_Y];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD V%X, V%X\n", _X, _Y);
	}
}

// add the value NN to register VX
void _7XNN(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _NN = (chip8->opcode & 0x00FF);

	chip8->V[_X] += _NN;

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - ADD V%X, %02X\n", _X, _NN);
	}
}

// add value of register VY to register VX (carry)
void _8XY4(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	if(chip8->V[_X] + chip8->V[_Y] > 255)
	{
		chip8->V[0xF] = 1;
	}
	else
	{
		chip8->V[0xF] = 0;
	}

	chip8->V[_X] += chip8->V[_Y];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - ADD V%X, V%X\n", _X, _Y);
	}
}

// subtract the value of register VY from regiser VX (borrow)
void _8XY5(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	if(chip8->V[_X] > chip8->V[_Y])
	{
		chip8->V[0xF] = 1;
	}
	else
	{
		chip8->V[0xF] = 0;
	}

	chip8->V[_X] -= chip8->V[_Y];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - SUB V%X, V%X\n", _X, _Y);
	}
}

// set register VX to the value of VY minus VX
void _8XY7(chip8_t *chip8)
{
	unsigned short int _X =(chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y =(chip8->opcode & 0x00F0) >> 4;

	if(chip8->V[_X] > chip8->V[_Y])
	{
		chip8->V[0xF] = 1;
	}
	else
	{
		chip8->V[0xF] = 0;
	}

	chip8->V[_X] = chip8->V[_Y] - chip8->V[_X];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - SUBN V%X, V%X\n", _X, _Y);
	}
}

// set VX to VX AND VY
void _8XY2(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	chip8->V[_X] &= chip8->V[_Y];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - AND V%X, V%X\n", _X, _Y);
	}
}

// set VX to VX OR VY
void _8XY1(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	chip8->V[_X] |= chip8->V[_Y];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - OR V%X, V%X\n", _X, _Y);
	}
}

// set VX to VX XOR VY
void _8XY3(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	chip8->V[_X] ^= chip8->V[_Y];

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - XOR V%X, V%X\n", _X, _Y);
	}
}

// store val of VY shifted right 1 bit in VX
void _8XY6(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	// least significant bit
	chip8->V[0xF] = (chip8->V[_Y] & 0x01);
	chip8->V[_X] = chip8->V[_Y] >> 1;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - SHR V%X, V%X\n", _X, _Y);
	}
}

// store val of VY shifted left 1 bit in VX
void _8XYE(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	// most significant bit
	chip8->V[0xF] = (chip8->V[_Y] >> 7);
	chip8->V[_X] = chip8->V[_Y] << 1; 

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - SHL V%X, V%X\n", _X, _Y);
	}
}

// set VX to a rnd number with mask of NN
void _CXNN(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _NN = (chip8->opcode & 0x00FF);

	srand(time(NULL));
	chip8->V[_X] = ((rand() % (0x0 - 0xFF)) + 0xFF) & _NN;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - RND V%X, %02X\n", _X, _NN);
	}
}

// Jump to address NNN
void _1NNN(chip8_t *chip8)
{
	unsigned short int _NNN = (chip8->opcode & 0x0FFF);

	chip8->pc = _NNN;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - JP %4X\n", _NNN);
	}
}

// jumpt to address NNN + V0
void _BNNN(chip8_t *chip8)
{
	unsigned short int _NNN = (chip8->opcode & 0x0FFF);

	chip8->pc = _NNN + chip8->V[0x0];
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - JP V0, %4X\n", _NNN);
	}
}

// execute subroutine starting at address NNN
void _2NNN(chip8_t *chip8)
{
	unsigned short int _NNN = (chip8->opcode & 0x0FFF);

	chip8->_stack[chip8->sp] = chip8->pc + 2;
	chip8->sp++;

	chip8->pc = _NNN;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - CALL %4X\n", _NNN);
	}
}

// return from a subroutine
void _00EE(chip8_t *chip8)
{
	chip8->sp--;
	chip8->pc = chip8->_stack[chip8->sp];
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - RET\n");
	}
}

// skip following instruction if VX = NN
void _3XNN(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _NN = (chip8->opcode & 0x0FF);

	if(chip8->V[_X] == _NN)
	{
		chip8->pc += 4;	
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SE V%X, %02X\n", _X, _NN);
		}
	}
	else
	{
		chip8->pc += 2;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SE V%X, %02X\n", _X, _NN);
		}
	}
}

// skip following instruction if VX == VY
void _5XY0(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	if(chip8->V[_X] == chip8->V[_Y])
	{
		chip8->pc += 4;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SE V%X, V%X\n", _X, _Y);
		}
	}
	else
	{
		chip8->pc += 2;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SE V%X, V%X\n", _X, _Y);
		}
	}
}

// skip following instruction if VX != NN
void _4XNN(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _NN = (chip8->opcode & 0x0FF);     

	if(chip8->V[_X] != _NN)
	{
		chip8->pc += 4;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SNE V%X, %02X\n", _X, _NN);
		}
	}
	else
	{
		chip8->pc += 2;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SNE V%X, %02X\n", _X, _NN);
		}
	}
}

// skip following instruction if VX != VY
void _9XY0(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4;

	if(chip8->V[_X] != chip8->V[_Y])
	{
		chip8->pc += 4;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SNE V%X, V%X\n", _X, _Y);
		}
	}
	else
	{
		chip8->pc += 2;
	
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SNE V%X, V%X\n", _X, _Y);
		}
	}
}

// set delay time to value of VX
void _FX15(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	chip8->delay_timer = chip8->V[_X];

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD DT, V%X\n", _X);
	}
}

// store current value of delay timer in VX
void _FX07(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	chip8->V[_X] = chip8->delay_timer;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD V%X, DT\n", _X);
	}
}

// set sound timer to the value of VX
void _FX18(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	chip8->sound_timer = chip8->V[_X];

	chip8->pc += 2;

	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD ST, V%X\n", _X);
	}
}

// wait for keypress and store result in VX
void _FX0A(chip8_t *chip8)
{
	unsigned int i;
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	const uint8_t *sdl_keys= SDL_GetKeyState(NULL);

	for(i = 0; i < KEY_SIZE; i++)
	{
		if(sdl_keys[_sdl_keymap[i]])
		{
			chip8->V[_X] = i;
			chip8->pc += 2;

			if(chip8->debug_flag == 1)
			{
				printf("[DEBG] - LD V%X, K\n", _X);
			}
		}
	}
}

// skip following instruction if key == VX pressed
void _EX9E(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	const uint8_t *sdl_keys = SDL_GetKeyState(NULL);

	if(sdl_keys[_sdl_keymap[chip8->V[_X]]])
	{
		chip8->pc += 4;
	
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SKP V%X\n", _X);
		}
	}
	else
	{
		chip8->pc += 2;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SKP V%X\n", _X);
		}
	}
}

// skip following instruction if key == VX not pressed
void _EXA1(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;
	const uint8_t *sdl_keys = SDL_GetKeyState(NULL);

	if(!sdl_keys[_sdl_keymap[chip8->V[_X]]])
	{
		chip8->pc += 4;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SKNP V%X\n", _X);
		}
	}
	else
	{
		chip8->pc += 2;
		
		if(chip8->debug_flag == 1)
		{
			printf("[DEBG] - SKNP V%X\n", _X);
		}
	}
}

// store NNN in I
void _ANNN(chip8_t *chip8)
{
	unsigned short int _NNN = (chip8->opcode & 0x0FFF);

	chip8->I = _NNN;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD I, %4X\n", _NNN);
	}
}

// add value stored in VX to I
void _FX1E(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	if(chip8->I + chip8->V[_X] > 0xFFF)
	{
		chip8->V[0xF] = 1;
	}
	else
	{
		chip8->V[0xF] = 0;
	}

	chip8->I += chip8->V[_X];

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - ADD I, V%X\n", _X);
	}
}

// draw sprite in pos VX, VY with N bytes of sprite data
// starting at the addr stored in I
// set VF = 1 if any set pixels are changed to unset
void _DXYN(chip8_t *chip8)
{
	unsigned int i, j;

	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8; 
	unsigned short int _Y = (chip8->opcode & 0x00F0) >> 4; 
	unsigned short int _N = (chip8->opcode & 0x000F);

	chip8->V[0xF] &= 0;

	for(i = 0; i < _N; i++) 
	{
		unsigned char pixel = chip8->memory[chip8->I + i];

		for(j = 0; j < 8; j++) 
		{
			if(pixel & (0x80 >> j)) 
			{
				if(chip8->graphics[j + chip8->V[_X] + (i + chip8->V[_Y]) * 64]) 
				{
					chip8->V[0xF] = 1;
				}

				chip8->graphics[j + chip8->V[_X] + (i + chip8->V[_Y]) * 64] ^= 1;
			}
		}
	}

	chip8->draw_flag = 1;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - DRW V%X, V%X, %02X\n", _X, _Y, _N);
	}
}

// clear screenhttp://mattmik.com/chip8.html
void _00E0(chip8_t *chip8)
{
	memset(chip8->graphics, 0, sizeof(chip8->graphics));

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - CLS\n");
	}
}

// set I to memory address of the sprite stored in VX
void _FX29(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	chip8->I = chip8->V[_X] * 5;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD F, V%X\n", _X);
	}
}

// store binary coded decimal == VX at address I, I+1 and I+2
void _FX33(chip8_t *chip8)
{
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	chip8->memory[chip8->I] = chip8->V[_X] / 100;
	chip8->memory[chip8->I + 1] = (chip8->V[_X] / 10) % 10;
	chip8->memory[chip8->I + 2] = chip8->V[_X] % 10;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD B, V%X\n", _X);
	}
}

// store values of V0 to VX including memory starting at addr I
// after operation, I = I + X + 1
void _FX55(chip8_t *chip8)
{
	unsigned int i = 0;
	unsigned short int _X= (chip8->opcode & 0x0F00) >> 8;

	for(i = 0; i <= _X; i++)
	{
		chip8->memory[chip8->I + i] = chip8->V[i];
	}

	chip8->I += _X + 1;

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD [I], V%X\n", _X);
	}
}

// fill regs V0 to VX including values of memory starting at I
// I = I + X + 1 after operation
void _FX65(chip8_t *chip8)
{
	unsigned int i;
	unsigned short int _X = (chip8->opcode & 0x0F00) >> 8;

	for(i = 0; i <= _X; i++)
	{	
		chip8->V[i] = chip8->memory[chip8->I + i];
	}

	chip8->pc += 2;
	
	if(chip8->debug_flag == 1)
	{
		printf("[DEBG] - LD V%X, [I]\n", _X);
	}
}

