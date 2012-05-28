#include <stdio.h>
#include <inttypes.h>

//取下一个2的幂
static unsigned int nextpow2(unsigned int num) 
{
    --num;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    return ++num;
}

int main()
{
	uint32_t ret = nextpow2(10);
	
	printf("nextpow2 is %u \n", ret);
	
	return 0;
}
