#include <ev.h>
#include <stdio.h> // for puts
#include <unistd.h>

// every watcher type has its own typedef'd struct
// with the name ev_TYPE
ev_io stdin_watcher;
ev_timer timeout_watcher;
ev_timer timeout_watcher2;

// all watcher callbacks have a similar signature
// this callback is called when data is readable on stdin
static void
stdin_cb (EV_P_ ev_io *w, int revents)
{
        printf ("stdin ready at %f\n", ev_now (EV_A));
        // for one-shot events, one must manually stop the watcher
        // with its corresponding stop function.
        //ev_io_stop (EV_A_ w);

        // this causes all nested ev_run's to stop iterating
        //ev_break (EV_A_ EVBREAK_ALL);
		char buf[16];
		read(w->fd, buf, 16);
		printf("recv %s\n", w->data);
		sleep(1);
}

// another callback, this time for a time-out
static void
timeout_cb (EV_P_ ev_timer *w, int revents)
{
        printf ("timeout at %f\n", ev_now (EV_A));

		//ev_now_update(EV_A);
        // this causes the innermost ev_run to stop iterating
        //ev_break (EV_A_ EVBREAK_ONE);
}

int
main (void)
{
        // use the default event loop unless you have special needs
        struct ev_loop *loop = EV_DEFAULT;
		char buf[16] = "hello";
        // initialise an io watcher, then start it
        // this one will watch for stdin to become readable
        ev_io_init (&stdin_watcher, stdin_cb, 0, EV_READ);
		stdin_watcher.data = buf;
        ev_io_start (loop, &stdin_watcher);

        // initialise a timer watcher, then start it
        // simple non-repeating 5.5 second timeout
        ev_timer_init (&timeout_watcher, timeout_cb, 0.3, 1);
        ev_timer_start (loop, &timeout_watcher);

		//ev_timer_init (&timeout_watcher2, timeout_cb, 0.3, 1); 
        //ev_timer_start (loop, &timeout_watcher2);

        // now wait for events to arrive
        ev_run (loop, 0);

        // break was called, so exit
        return 0;
}

