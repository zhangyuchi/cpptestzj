#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i=0;
	srand(100);
	for(; i<100; ++i)
	{
		printf("%d | ", rand() );
	}

	printf("\n");
	return 0;
}
