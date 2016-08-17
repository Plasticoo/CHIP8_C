#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

void print_exit_error(unsigned int error_code, char *error_string)
{
	switch(error_code)
	{
		// file 
		case 2:
			printf("[ERROR 2] - Can't open file.\n");
			exit(OPEN_ERROR);
		case 3:
			printf("[ERROR 3] - File size is invalid.\n");
			exit(SIZE_ERROR);
		// args
		case 4:
			printf("[ERROR 4] - Not enough arguments.\n");
			exit(ARGS_ERROR);
		// vid
		case 5:
			printf("[ERROR 5] - Unable to init SDL: %s.\n", error_string);
			exit(SDL_INIT_ERROR);
		case 6:
			printf("[ERROR 6] - Unable to set video: %s.\n", error_string);
			exit(SDL_VIDEO_ERROR);
	}
}
