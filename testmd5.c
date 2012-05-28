#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void md5_to_str(uint8_t *md5, uint32_t len, uint8_t *str)
{
	int i=0;
    for ( ; i<len; ++i)
    {
        snprintf(str, 3, "%02x", *(md5+i));
        str += 2;
    }
}

void str_to_md5(uint8_t *str, uint32_t len, uint8_t *md5)
{
    int i=0;
    for ( ; i<len; )
    {
        sscanf(str, "%02x", md5);
        str += 2;
        md5 += 1;
        i += 2;
    }
}

int main()
{
	uint8_t *str = (uint8_t *)calloc(33, sizeof(uint8_t));
	uint8_t *md5 = (uint8_t *)calloc(16, sizeof(uint8_t));

	strcpy(str, "0000012345678abcdef0");
	str_to_md5(str, 20, md5);

	int i = 0;
	for ( ; i<8; ++i)
	{
		printf("0x%02x ", *(md5+i));
	}	

	printf("\n");

	uint8_t str2[33];
	str2[0] = 0;

	md5_to_str(md5, 10, str2);

	printf("str2 len is %d\n", strlen(str2));

	printf("%s\n", str2);

	return 0;
}

