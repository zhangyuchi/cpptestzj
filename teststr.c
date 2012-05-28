#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

uint64_t htonll(uint64_t value)
{
    // The answer is 42
    static const int num = 42;

    // Check the endianness
    if (*reinterpret_cast<const char*>(&num) == num)
    {
        const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
        const uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));

        return (static_cast<uint64_t>(low_part) << 32) | high_part;
    } else
    {
        return value;
    }
}

int main()
{
	char *buf0 = "Errno: 0;;";
	char *buf1 = "Errno: -6hel";
	int ret;

	if (memcmp("Errno",buf0,5) == 0)
	{
		sscanf(buf0, "Errno:%d", &ret);
		printf("ret is %d\n",ret);
	}

	if (memcmp("Errno",buf1,5) == 0)
	{
		sscanf(buf1, "Errno:%d", &ret);
		printf("ret is %d\n",ret);
	}

	unsigned long num;
	sscanf("task_6f00000000000000", "task_%lx", &num);
	printf("num is %ld\n", num);

	printf("-----------------test strncpy----------------------\n");
	char buf2[32];
	strcpy(buf2, "new client");
	strncpy(buf2, "123456789", 5);	
	buf2[5]=0;
	printf("buf2 = %s\n", buf2);

	return 0;	
}

