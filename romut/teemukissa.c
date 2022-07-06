
#include <stdio.h>


int main (void)
{

	int a[3] = {1, 20, 40};

	printf("%d\n", a[2]);
	printf("%d\n", *(a+2));
	printf("%d\n", *(2 + a));




	printf("%d\n", 2[a]);
	printf("%d\n", 0x2[a]);
	



	return (0);
}