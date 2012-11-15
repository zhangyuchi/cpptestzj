/*
 * =============================================================================
 *
 *       Filename:  testcounter_ck.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月29日 15时55分16秒
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
#include <ck_pr.h>

uint64_t value;

static void *
counter(void *unusued)
{
    uint64_t previous = 0, updated;

    for (;;) {
        updated = ck_pr_faa_64(&value, 1) + 1;
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

