#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <time.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "event.h"
#include "evhttp.h"
#include "glib.h"

typedef struct 
{
	struct event ev_timeout;
	struct timeval tv;
	struct event_base *base;
} time_slot_t;

void retimer(time_slot_t *ts)
{
	ts->tv.tv_sec=1;
	ts->tv.tv_usec=0;
	evtimer_add(&ts->ev_timeout, &ts->tv);
}

void printheader(struct evkeyvalq *headers)
{
	struct evkeyval *header;
	TAILQ_FOREACH(header, headers, next)
	{
		printf("%s : %s\n",header->key, header->value);
	}
}

void response_cb(struct evhttp_request* req, void *arg)
{
	if (req)
	{
		printheader(req->input_headers);		
		printf("response is %s\n", req->input_buffer->buffer);
	}
	else
		printf("req is %p, arg is %p\n", req, arg);
}

void makehttp1req(time_slot_t *ts)
{
	struct evhttp_connection* evcon = evhttp_connection_new("ch06.cc.dxt.qihoo.net", 8360);
	printf("evcon is %p\n", evcon);

	evhttp_connection_set_base( evcon, NULL/*ts->base*/ );

	struct evhttp_request * req = evhttp_request_new( response_cb, NULL);
	printf("req is %p\n", req);
	evhttp_add_header(req->output_headers, "host", "ch06.cc.dxt.qihoo.net" );
	evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/get.do?space=XT_Test&k=filepipe_monitor_1");
}

void makehttp2req(time_slot_t *ts)
{
	struct evhttp_connection* evcon = evhttp_connection_new("www.gnu.org", 80);
	printf("evcon is %p\n", evcon);
	struct evhttp_request * req = evhttp_request_new( response_cb, NULL);
	printf("req is %p\n", req);
	evhttp_add_header(req->output_headers, "host", "www.gnu.org" );
	evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/software/libc/manual/html_mono/libc.html");
}

void timeout_cb (int sockfd, short event, void* arg)
{
	int fd=0;
	printf("%p  %d :timer timeout %d\n", arg, fd, event);

	if ( arg )
	{
		time_slot_t *ts = arg;
		//retimer(ts);
		makehttp1req(ts);
	}
}

int main ()
{
    struct event ev_accept;

    g_print("server_proc_main init .\n");

    struct event_base *base = event_init ();

    /* We now have a listeing socket, we create a read event to
     * be notified when a client connects. */
	time_slot_t *ts = (time_slot_t *)calloc(1,sizeof(time_slot_t));

	ts->tv.tv_sec=1;
	ts->tv.tv_usec=0;
	ts->base = base;
	evtimer_set(&ts->ev_timeout, timeout_cb, ts);
	event_base_set(base, &ts->ev_timeout);
	evtimer_add(&ts->ev_timeout, &ts->tv);
    
	event_base_loop(base, 0);
    return 0;
}

