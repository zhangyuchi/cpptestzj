#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/time.h>

int unalign_cmp(const char *l, const char *r, int len)
{
    return memcmp(l, r, len);
}

#define SP_ALIGN 8
typedef unsigned long long align_type;

int align_cmp(const char *l, const char *r, int len)
{
    ptrdiff_t n = len;
    ptrdiff_t c = n - (SP_ALIGN-1);
    ptrdiff_t i = 0;
    for (; i < c; i += SP_ALIGN)
        if (*reinterpret_cast<const align_type*>(l + i) !=
                *reinterpret_cast<const align_type*>(r + i))
            break;

    printf("i=%ld\n", i);

    for (; i < n; ++i)
        if (l[i] != r[i])
            return (unsigned char)l[i] < (unsigned char)r[i];

    return 0;
}

int main()
{
    FILE* fp = fopen("test.dat", "r");

    const int buflen = 102400;    
    char buf1[buflen] = {0};
    char buf2[buflen] = {0};

    size_t buf1len = fread(buf1, 1, buflen, fp);
    fseek(fp, 0L, SEEK_SET);
    size_t buf2len = fread(buf2, 1, buflen, fp);

    printf("%lu:%lu\n", buf1len, buf2len);

    struct timeval start_tv;
    struct timeval end_tv;
    gettimeofday(&start_tv, NULL);

    int diff = align_cmp(buf1, buf2, buflen);

    gettimeofday(&end_tv, NULL);
    double tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;

    printf("spend %f microseconds, diff = %d\n", tt, diff);

    return 0;
}
