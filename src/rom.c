#include <stdio.h>

#include "rom.h"
#include "errors.h"

int rom_size(FILE* rom_file)
{
	unsigned int size;

	fseek(rom_file, 0L, SEEK_END);
	size = ftell(rom_file);
	fseek(rom_file, 0L, SEEK_SET);

	return size;
}

int rom_load(chip8_t *chip8, char *rom_name)
{
	FILE *rom_file;

	unsigned int i, c;

	printf("[INFO] - Loading ROM into memory...\n");

	// load rom
	if((rom_file = fopen(rom_name, "rb")) == NULL)
	{
		print_exit_error(OPEN_ERROR, NULL);
	}
  
	if(rom_size(rom_file) > 3584 || rom_size(rom_file) < 0)
	{
		print_exit_error(SIZE_ERROR, NULL);	
	}

	printf("[INFO] - Loaded %d bytes into memory.\n", rom_size(rom_file));

	// import to memory
	for(i = 0; (int)(c = fgetc(rom_file)) != EOF; i++) 
	{
        chip8->memory[0x200 + i] = c;
    }

	fclose(rom_file);

	return 0;
}
