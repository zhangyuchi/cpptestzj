#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct bitmap_tag
{
    uint8_t *bits;
    uint32_t length;
} bitmap_t;

bitmap_t *bitmap_new( uint32_t length )
{
    uint8_t *bits = calloc(1,length);
    if ( NULL == bits )
        return NULL;

    bitmap_t *bitmap = calloc(1,sizeof(bitmap_t));
    if ( NULL == bitmap )
    {
        free(bits);
        return NULL;    
    }

    bitmap->bits = bits;
    bitmap->length = length;

    return bitmap;
}

void bitmap_free( bitmap_t *bitmap )
{
    free(bitmap->bits);
    free(bitmap);
}

void set(bitmap_t *bitmap, int i)
{
    if ( bitmap )
        bitmap->bits[i >> 3] |= (0x80 >> (i & 7));
}

void clear(bitmap_t *bitmap, int i)
{
    if ( bitmap )
        bitmap->bits[i >> 3] &= ~(0x80 >> (i & 7));
}

int main()
{
	bitmap_t *bm = bitmap_new(4);

	set(bm, 0);
	set(bm, 1);
	set(bm, 11);

	uint32_t i=0;

	for( ; i<bm->length; ++i)
	{
		printf("%02x ", bm->bits[i]);	
	}

	return 0;
}

