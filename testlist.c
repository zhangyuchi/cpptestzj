#include <stdio.h>

#define list_entry(ptr, type, member) \
        ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

typedef struct 
{
	int first;
	char second;
	void *third;
	float fourth;
	long fiveth;
} mys_t;

int main()
{
	mys_t mys;
	mys_t *p = &mys;

	printf("mys is %p\n", p);
	printf("mys is %p\n", list_entry(&p->first, mys_t, first));
	printf("mys is %p\n", list_entry(&p->second, mys_t, second));
	printf("mys is %p\n", list_entry(&p->third, mys_t, third));
	printf("mys is %p\n", list_entry(&p->fourth, mys_t, fourth));
	printf("mys is %p\n", list_entry(&p->fiveth, mys_t, fiveth));

	return 0;
}

