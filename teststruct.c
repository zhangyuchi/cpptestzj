#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
	int len;
	char buf[];
} buffer;

int main()
{
	printf("buffer size is %Zd\n", sizeof(buffer));

	char *data = calloc(1,102);

	int len = 16;
	memcpy(data, &len, sizeof(len));
	memcpy(data+sizeof(len), "01234567890123456789", 20);

	buffer *b = (buffer*)data;
	printf("b is %p\n",b);
	printf("b len is %d\n",b->len);
	printf("b buf is %s\n",b->buf);

	char *neda = malloc(1032);
	strcpy(neda, "1231222222222222222222222222222222222222222222222222222");
	printf("neda is %p\n",neda);

	data = realloc(data, 2048);

    b = (buffer*)data;
	printf("b is %p\n",b);
    printf("b len is %d\n",b->len);
    printf("b buf is %s\n",b->buf);

	return 0;
}

