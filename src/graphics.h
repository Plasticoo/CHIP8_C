#ifndef _graphics_h
#define _graphics_h

#include <SDL/SDL.h>

#include "cpu.h"

void fps_lock(unsigned int next_frame, unsigned int max_fps);
void graphics_init(SDL_Surface **screen, char *title_name);
void graphics_clear(SDL_Surface *screen);
void draw_pixel(SDL_Surface *screen, int x, int y);
void graphics_update(SDL_Surface *screen, chip8_t *chip8);
void graphics_quit();

#endif
