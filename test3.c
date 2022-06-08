

#include <string.h>
#include <stdio.h>

void move_stack_one_index_up(int *stack, size_t len)
{
	int *dst;
	int *src;

	src = stack;
	dst = stack + 1;
	memmove(dst,src ,len);
}

int main (void)
{
	int array[100] = {1, 2 , 3 , 4 , 5, 6, 7, 0};


	move_stack_one_index_up(array, 7);
	
	int i = 0;

	while (i != 10)
	{
		printf("%i\n", array[i++]);
	}


	return 0;
}