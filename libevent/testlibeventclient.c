/*
 * =============================================================================
 *
 *       Filename:  testlibeventclient.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月02日 10时39分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
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

#include "event.h"




int main ()
{
    struct event ev_accept;

    printf("server_proc_main init .\n");

	int listenfd = create_socket( NULL, 9009, SOCK_STREAM);
    if (listenfd < 0)
    {
        g_print("tcp_listen failed!\n");
        return -1;
    }	

    // initialize libevent.
    struct event_base *base = event_init ();

	event_set (&ev_accept, listenfd, EV_READ | EV_PERSIST,
             	conn_accept, NULL);

   	struct timeval tvaccept;
	tvaccept.tv_sec=3;
	tvaccept.tv_usec=3;

    event_add (&ev_accept, &tvaccept);

    
    event_dispatch ();

    return 0;
}

