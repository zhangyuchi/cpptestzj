#include <stdio.h>

int test(){
	char ovbuf[7];
   	int i;
    for (i=0; i<7; i++) ovbuf[i]='x';
   	snprintf(ovbuf, 4, "foo%s", "bar");
   	if (ovbuf[5]!='x') return 1;
   	snprintf(ovbuf, 4, "foo%d", 666);
	if (ovbuf[5]!='x') return 1;
	return 0;
}

int main() {
	int r;
	r = test();
	printf("ret = %d\n", r);
	return 0;
}
