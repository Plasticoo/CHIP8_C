#include <SDL/SDL.h>

#include "cpu.h"
#include "graphics.h"
#include "memory.h"

SDLKey sdl_keys[16] = 
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

int input_wait()
{
	SDL_Event event;

	unsigned int i;

	SDL_WaitEvent(&event);

	if(event.type == SDL_KEYDOWN)
	{
		for(i = 0; i < KEY_SIZE; i++)
		{
			if(sdl_keys[i] == event.key.keysym.sym)
			{
				return i;
			}
		}
	}

	return -1;
}

int input_new_event(chip8_t *chip8)
{
	SDL_Event event;
	
	const Uint8 *sdl_key = SDL_GetKeyState(NULL);
	
	unsigned int i;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return 1;
				break;
			case SDL_KEYDOWN:
				for(i = 0; i < KEY_SIZE; i++)
				{
					if(sdl_keys[i] == event.key.keysym.sym)
					{
						chip8->keys[i] = 1;
						break;
					}
				}
				break;
			case SDL_KEYUP:
				for(i = 0; i < KEY_SIZE; i++)
				{
					if(sdl_keys[i] == event.key.keysym.sym)
					{
						chip8->keys[i] = 0;
						break;
					}
				}
				break;
			default:
				break;
		}
	}

	if(sdl_key[SDLK_g])
	{
		if(chip8->debug_flag == 0)
		{
			chip8->debug_flag = 1;
		}
		else
		{
			chip8->debug_flag = 0;
		}
	}
	else if(sdl_key[SDLK_h])
	{
		memory_print_emu_info(chip8);	
	}
	else if(sdl_key[SDLK_ESCAPE])
	{
		printf("[INFO] - Exiting...\n");
		graphics_quit();
		exit(EXIT_SUCCESS);	
	}

	return 0;
}
