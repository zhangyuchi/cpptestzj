#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
	unsigned flag1:1; //表示位段，flag1只占1bit
	unsigned flag2:1;
	unsigned flag3:1;
	unsigned flag4:1;
} types_t;

typedef struct{
	uint8_t buff[16];
	uint8_t buff1[8];
	int flag;
} mys_t;

typedef struct{
	mys_t in;
} myss_t;

void printnum( int n)
{
	printf("n = %d\n",n);
}

void printfloat( float f)
{
	printf("f = %f\n",f);
}

int main()
{
	types_t types;
	printf("flag bytes is %Zd \n", sizeof(types));
	printf("uint64 bytes is %Zd \n", sizeof(uint64_t));
	printf("long long bytes is %Zd \n", sizeof(long long));

	printf("----------------------------------------------------\n");

	printf("mys_t size is %Zd, myss_t size is %Zd\n", sizeof(mys_t),sizeof(myss_t) );

	printf("----------------------------------------------------\n");
	mys_t mys;
	mys_t *p_mys = &mys;
	uint64_t number = 0x1234567812345678;
	memcpy(mys.buff1, (uint8_t *)&number, 8);

	uint64_t i,j;
	i = (uint64_t)(&mys);
	j = i + sizeof(mys);
	
	uint64_t transn;
	transn = *((uint64_t *)p_mys->buff1);
	printf("mys address is %lx, size is %Zd, transn is %lx\n", i, sizeof(mys), transn );
	

	for(; i<j; ++i )
	{
		printf("%02x ",*(uint8_t *)i);
	} 

	printf("\n");

	unsigned int num = 1577777;
	printf("num is %d\n", num);
	--num;
	printf("num is %d\n", num);
    num |= num >> 1;
	printf("num is %d\n", num);
    num |= num >> 2;
	printf("num is %d\n", num);
    num |= num >> 4;
	printf("num is %d\n", num);
    num |= num >> 8;
	printf("num is %d\n", num);
    num |= num >> 16;
	printf("num is %d\n", num);
	++num;

	printf("num is %d\n", num);

	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//int d = 1459/8;

	float f = 13/3.0;

	printf("init f = %f\n", f);
	printnum(ceilf(f));	
	printnum(floorf(f));	

	time_t now;
	printf("time_t size is %ld\n", sizeof(now) );

	bool Bs;
	printf("bool size is %ld\n", sizeof(Bs) );

    int nullsize = 0;
    char nullbuf[nullsize];

    printf("nullbuf size is %ld\n", sizeof(nullbuf) );

	return 0; 
}

