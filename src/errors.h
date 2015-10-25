#ifndef __ERRORS_H_
#define __ERRORS_H_

#define OPEN_ERROR 2
#define SIZE_ERROR 3
#define ARGS_ERROR 4
#define SDL_INIT_ERROR 5
#define SDL_VIDEO_ERROR 6

void print_exit_error(unsigned int error_code, char *error_string);

#endif
