/* The Computer Language Benchmarks Game
 * http://benchmarksgame.alioth.debian.org/

   contributed by Mr Ledrug
*/

#ifndef _GNU_SOURCE 
  #define _GNU_SOURCE
#endif

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

char *pairs = "ATCGGCTAUAMKRYWWSSYRKMVBHDDHBVNN\n\n";
char tbl[128];

typedef struct work_s work_t;
struct work_s {
    pthread_t id;
    work_t *next;
    char *begin, *end;
};

void *process(void *ww) {
    work_t *w = (work_t *)ww;
    char *from = w->begin, *to = w->end;
    while (*from++ != '\n');

    size_t len = to - from;
    size_t off = 60 - (len % 61);

    if (off) {
        char *m;
        for (m = from + 60 - off; m < to; m += 61) {
            memmove(m + 1, m, off);
            *m = '\n';
        }
    }

    char c;
    for (to--; from <= to; from++, to--)
        c = tbl[(int)*from], *from = tbl[(int)*to], *to = c;

    return 0;
}

int doit(char*buf, size_t buflen) {
    if ( !buf || !buflen )
        return -1;

    char *s;
    for (s = pairs; *s; s += 2) {
        tbl[toupper(s[0])] = s[1];
        tbl[tolower(s[0])] = s[1];
    }

    size_t end = buflen;
    //buf[end] = '>';

    work_t *work = 0;
    char *from, *to = buf + end - 1;
    while (1) {
        for (from = to; *from != '>'; from--);

        work_t *w = (work_t *)malloc(sizeof(work_t));
        w->begin = from;
        w->end = to;
        w->next = work;
        work = w;

        pthread_create(&w->id, 0, process, w);

        to = from - 1;
        if (to < buf) break;
    }

    while (work) {
        work_t *w = work;
        work = work->next;
        pthread_join(w->id, 0);
        free(w);
    }

    //write(fileno(stdout), buf, end);
    return 0;
}
