#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void  returnarray(uint8_t *a)
{
	uint64_t num;

	num = rand();
 	num = (num << 32) | num;

	printf("real num is %ld\n", num);

	memcpy(a, (uint8_t *)&num, 8);
} 

int main()
{
	uint8_t result[8];
	returnarray(result);

	uint32_t frontnum;
	uint32_t endnum;

	frontnum = *((uint32_t *)result);
	endnum = *((uint32_t *)(result+4));

	printf("size of result is %Zd\n", sizeof(result));
	printf("tran num is %d%d\n", frontnum, endnum);

	return 0;
}


