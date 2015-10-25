#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>

#include "cpu.h"
#include "rom.h"
#include "main.h"
#include "errors.h"
#include "memory.h"
#include "graphics.h"
#include "input.h"

#define FPS_MAX 5

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	chip8_t _chip8;

	unsigned int next_frame = SDL_GetTicks() + FPS_MAX;

	if(argc != 2)
	{
		print_exit_error(ARGS_ERROR, NULL);
	}

	printf("[INFO] - Setting up emulator...\n");

	// chip8 inits
	cpu_init_reset(&_chip8);
	rom_load(&_chip8, argv[1]);	

	graphics_init(&screen, argv[1]);

	// program loop
	for(;;)
	{
		cpu_cycle(&_chip8);

		if(_chip8.draw_flag)
		{
			graphics_update(screen, &_chip8);
			_chip8.draw_flag = 0;	
		}

		if(input_new_event(&_chip8) == 1)
		{
			break;	
		}

		fps_lock(next_frame, FPS_MAX);
		next_frame = SDL_GetTicks() + FPS_MAX;
	}
	
	graphics_quit();

	return 0;
}
