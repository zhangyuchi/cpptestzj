#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <event.h>

void time_cb(int fd, short event, void *arg)
{
        struct timeval tv;
        struct event *ev = NULL;
        // add your code here
        fprintf(stderr, "Hello, evtimer\n");
        ev = malloc(sizeof(struct event));
        tv.tv_sec = 0;
        tv.tv_usec = 50000L;
        evtimer_set(ev, time_cb, ev);
        evtimer_add(ev, &tv);
}
int main(int argc, char *argv)
{
        struct timeval tv;
        struct event *ev = NULL;
        event_init();
        ev = malloc(sizeof(struct event));
        tv.tv_sec = 0;
        tv.tv_usec = 50000L;
        evtimer_set(ev, time_cb, ev);
        evtimer_add(ev, &tv);
        event_dispatch();
        return 0;
}

