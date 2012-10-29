/*
 * =============================================================================
 *
 *       Filename:  testcounter.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月29日 15时29分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//volatile uint64_t value=0;
uint64_t value=0;

static void *
counter(void *unusued)
{
    uint64_t previous = 0, updated;

    for (;;) {
        updated = ++value;
        if (previous >= updated) {
            fprintf(stderr, "ERROR: %" PRIu64 " >= %" PRIu64 "\n", 
                    previous, updated);
            exit(EXIT_FAILURE);
        }
        previous = updated;
    }

    return (NULL);
}

int
main(int argc, char *argv[])
{
    pthread_t a, b, c, d;

    pthread_create(&a, NULL, counter, NULL);
    pthread_create(&b, NULL, counter, NULL);
    pthread_create(&c, NULL, counter, NULL);
    pthread_create(&d, NULL, counter, NULL);

    pthread_join(a, NULL);
    return (0);
}

