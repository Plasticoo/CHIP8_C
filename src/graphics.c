#include <stdio.h>
#include <SDL/SDL.h>

#include "graphics.h"
#include "errors.h"

void fps_lock(unsigned int next_frame, unsigned int max_fps)
{
	unsigned int n_ticks = SDL_GetTicks();

	if(next_frame < n_ticks)
	{
		return;
	}

	if(next_frame > (n_ticks + max_fps))
	{
		SDL_Delay(max_fps);
	}
	else
	{
		SDL_Delay(next_frame - n_ticks);
	}
}

void graphics_init(SDL_Surface **screen, char *title_name)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		print_exit_error(SDL_INIT_ERROR, SDL_GetError()); 
    }

    *screen = SDL_SetVideoMode(64 * 8, 32 * 8, 8, SDL_SWSURFACE);
    if (*screen == NULL) 
	{
		print_exit_error(SDL_VIDEO_ERROR, SDL_GetError());
    }

	SDL_WM_SetCaption(title_name, NULL);
}

void graphics_clear(SDL_Surface *screen)
{
    SDL_FillRect(screen, NULL, 0);
}

void draw_pixel(SDL_Surface *screen, int x, int y)
{
    Uint8 *pixel;
    unsigned int i, j;

    pixel = (Uint8 *)screen->pixels + (y * 8) * screen->pitch + (x * 8);
    for (i = 0; i < 8; i++) 
	{
        for (j = 0; j < 8; j++) 
		{
            pixel[j] = 0xFF;
        }

        pixel += screen->pitch;
    }
}

void graphics_update(SDL_Surface *screen, chip8_t *chip8)
{
    unsigned int x, y;

    if(SDL_MUSTLOCK(screen)) 
	{
        SDL_LockSurface(screen);
    }

    graphics_clear(screen);
    for(y = 0; y < 32; y++) 
	{
        for(x = 0; x < 64; x++) 
		{
            if(chip8->graphics[x + (y * 64)]) 
			{
                draw_pixel(screen, x, y);
            }
        }
    }

    if(SDL_MUSTLOCK(screen)) 
	{
        SDL_UnlockSurface(screen);
    }

    SDL_Flip(screen);
}

void graphics_quit()
{
    SDL_Quit();
}
