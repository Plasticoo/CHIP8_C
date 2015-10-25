#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int variable = 0;
	int variable_array[10] = {0};

	printf("Sizeof variable: %d\nSizeof array: %d\n", 
			(int)sizeof(variable), (int)sizeof(variable_array));
}
