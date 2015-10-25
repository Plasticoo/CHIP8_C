#include <stdio.h>
#include <stdlib.h>

void print_opcode(unsigned char *buffer, unsigned int pcounter)
{
	unsigned char *p_code = &buffer[pcounter];
	unsigned int opcode = (p_code[0] << 8) | (p_code[1]);

	unsigned short int _X = (opcode & 0x0F00) >> 8;
	unsigned short int _Y = (opcode & 0x00F0) >> 4;
	unsigned short int _N = (opcode & 0x000F);
	unsigned short int _NN = (opcode & 0x00FF);
	unsigned short int _NNN = (opcode & 0x0FFF);

	switch(opcode & 0xF000)
	{
		case 0x0000:
			switch(opcode & 0x00FF)
			{
				case 0x00E0:
					printf("%04X - %02X%02X - CLS\n", 
							pcounter, p_code[0], p_code[1]);
					break;
				case 0x00EE:
					printf("%04X - %02X%02X - RET\n", 
							pcounter, p_code[0], p_code[1]);
					break;
				default:
					printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
			}
			break;
		case 0x1000:
			printf("%04X - %02X%02X - JP %04X\n", 
					pcounter, p_code[0], p_code[1], _NNN);
			break;
		case 0x2000:
			printf("%04X - %02X%02X - CALL %04X\n", 
					pcounter, p_code[0], p_code[1], _NNN);
			break;
		case 0x3000:
			printf("%04X - %02X%02X - SE V%X, %02X\n", 
					pcounter, p_code[0], p_code[1], _X, _NN);
			break;
		case 0x4000:
			printf("%04X - %02X%02X - SNE V%X, %02X\n", 
					pcounter, p_code[0], p_code[1], _X, _NN);
			break;
		case 0x5000:
			printf("%04X - %02X%02X - SE V%X, V%X\n", 
					pcounter, p_code[0], p_code[1], _X, _Y);
			break;
		case 0x6000:
			printf("%04X - %02X%02X - LD V%X, %02X\n", 
					pcounter, p_code[0], p_code[1], _X, _NN);
			break;
		case 0x7000:
			printf("%04X - %02X%02X - ADD V%X, %02X\n", 
					pcounter, p_code[0], p_code[1], _X, _NN);
			break;
		case 0x8000:
			printf("%04X - %02X%02X - RET\n", pcounter, p_code[0], p_code[1]);
			switch(opcode & 0x000F)
			{
				case 0x0:
					printf("%04X - %02X%02X - LD V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x1:
					printf("%04X - %02X%02X - OR V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x2:
					printf("%04X - %02X%02X - AND V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x3:
					printf("%04X - %02X%02X - XOR V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x4:
					printf("%04X - %02X%02X - ADD V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x5:
					printf("%04X - %02X%02X - SUB V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x6:
					printf("%04X - %02X%02X - SHR V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0x7:
					printf("%04X - %02X%02X - SUBN V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				case 0xE:
					printf("%04X - %02X%02X - SHL V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				default:
					printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
			}
			break;
		case 0x9000:
			switch(opcode & 0x000F)
			{
				case 0x0:
					printf("%04X - %02X%02X - SNE V%X, V%X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y);
					break;
				default:
					printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
			}
			break;
		case 0xA000:
					printf("%04X - %02X%02X - LD I, %04X\n", 
							pcounter, p_code[0], p_code[1], _NNN);
			break;
		case 0xB000:
					printf("%04X - %02X%02X - JP V0, %04X\n", 
							pcounter, p_code[0], p_code[1], _NNN);
			break;
		case 0xC000:
					printf("%04X - %02X%02X - RND V%X, %02X\n", 
							pcounter, p_code[0], p_code[1], _X, _NN);
			break;
		case 0xD000:
					printf("%04X - %02X%02X - DRW V%X, V%X, %02X\n", 
							pcounter, p_code[0], p_code[1], _X, _Y, _N);
			break;
		case 0xE000:
					printf("%04X - %02X%02X - RET\n", pcounter, p_code[0], p_code[1]);
			switch(opcode & 0x00FF)
			{
				case 0x9E:
					printf("%04X - %02X%02X - SKP V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0xA1:
					printf("%04X - %02X%02X - SKNP V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				default:
					printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
			}
			break;
		case 0xF000:
			switch(opcode & 0x00FF)
			{
				case 0x07:
					printf("%04X - %02X%02X - LD V%X, DT\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x0A:
					printf("%04X - %02X%02X - LD V%X, K\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x15:
					printf("%04X - %02X%02X - LD DT, V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x18:
					printf("%04X - %02X%02X - LD ST, V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x1E:
					printf("%04X - %02X%02X - ADD I, V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x29:
					printf("%04X - %02X%02X - LD F, V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x33:
					printf("%04X - %02X%02X - LD B, V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x55:
					printf("%04X - %02X%02X - LD [I], V%X\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				case 0x65:
					printf("%04X - %02X%02X - LD V%X, [I]\n", 
							pcounter, p_code[0], p_code[1], _X);
					break;
				default:
					printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
			}
			break;
		default:
			printf("%04X - %02X%02X - Unknown\n", pcounter, p_code[0], p_code[1]);
	}
}

int main(int argc, char *argv[])
{
	FILE* rom_file;

	unsigned int pc = 0x200;
	unsigned int file_size;

	unsigned char *buffer;

	if((rom_file = fopen(argv[1], "rb")) == NULL)
	{
		printf("[ERROR] - Couldn't open file!\n");
		exit(EXIT_FAILURE);
	}

	fseek(rom_file, 0L, SEEK_END);
	file_size = ftell(rom_file);
	fseek(rom_file, 0L, SEEK_SET);

	buffer = malloc(file_size + pc);
	fread(buffer + pc, file_size, 1, rom_file);
	fclose(rom_file);

	while(pc < (file_size + 0x200))
	{
		print_opcode(buffer, pc);
		pc += 2;
	}

	putchar('\n');

	free(buffer);

	return 0;
}
