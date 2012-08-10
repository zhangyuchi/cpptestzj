/*
 * =============================================================================
 *
 *       Filename:  testhash.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月03日 14时36分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint64_t hash_o2o(uint8_t *str, uint32_t len, uint64_t max)
{
    uint64_t hash = 0;
    uint32_t i=0;

    for( ; i<len; ++i)
    {
        hash += *str++;
    }

    return hash & max;
}

int main(int argc, char **argv)
{
    if (argc<2)
    {
        printf("usage hash str\n");
        return 1;
    }

    uint64_t h = hash_o2o(argv[1], strlen(argv[1]), 1000);

    printf("%lu\n", h);

    return 0;
}

