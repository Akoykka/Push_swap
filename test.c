#include <stdio.h>
#include <unistd.h>




int  main (int argc, char **argv)
{
if (argc == 2)
	printf("%s\n", argv[1]);

int i = 0;
while (argv[1][i])
{
	write(1, &argv[1][i], 1);
	++i;
}
	write(1, &argv[1][i], 1);
return 0;
}