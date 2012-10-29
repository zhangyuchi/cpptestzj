/*
 * =============================================================================
 *
 *       Filename:  testsetsig.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月29日 15时14分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <stdio.h>
#include <pthread.h>

static unsigned int signal;

static void *
wait_for_signal(void *unused)
{
    signal = 1;

    puts("[T] Testing signal.");

    while (signal == 1);

    puts("[T] We have received the signal.");
    return (NULL);
}

int
main(int argc, char *argv[])
{
    pthread_t a;
    unsigned int i;

    pthread_create(&a, NULL, wait_for_signal, NULL);

    for (i = 0; i < 10; i++) {
        puts("[M] Setting signal...");
        sleep(1);
        signal = 0;
    }
    pthread_join(a, NULL);

    return (0);
}

