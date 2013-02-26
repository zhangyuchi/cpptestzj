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
#include "glib.h"

typedef struct{ 
    int sockfd;
    struct event ev_read;
    struct event ev_write;

    struct evbuffer *input;
    struct evbuffer *output;
    struct timeval tv;
} connection_t;

typedef struct 
{
    struct event ev_timeout;
    struct timeval tv;
} time_slot_t;

connection_t *conn_new()
{
    connection_t *conn = NULL;

    conn = calloc (1, sizeof  (connection_t));
    if (conn == NULL)
        return NULL;

    conn->input = evbuffer_new();
    if (conn->input == NULL)
    {
        free(conn);
        return NULL;
    }

    conn->output = evbuffer_new();
    if (conn->output == NULL)
    {
        free(conn);
        evbuffer_free(conn->input);
        return NULL;
    }

    return conn; 
}

int create_socket(const char* ip, int port, int type)
{
    int sockfd = -1;
    int flags = 1;
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (ip != NULL)
    {
        inet_pton(AF_INET, ip, &servaddr.sin_addr);
    }
    else
    {
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    sockfd = socket(AF_INET, type, 0);
    if (sockfd == -1)
    {
        g_warning("socket() failed! %s", strerror(errno));
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in)) == -1)
    {
        close(sockfd);
        g_warning("bind() failed! %s", strerror(errno));
        return -1;
    }

    if (type == SOCK_STREAM)
    {
        if (listen(sockfd, SOMAXCONN) == -1)
        {
            close(sockfd);
            g_warning("listen() failed! %s", strerror(errno));
            return -1;
        }
    }

    return sockfd;
}

void timeout_cb (int sockfd, short event, void* arg)
{
    int fd=0;
    connection_t *conn = NULL;
    printf("%p  %d :timer timeout %d\n", arg, fd, event);

    if ( arg ){
        time_slot_t *ts = (time_slot_t *)arg;
        ts->tv.tv_sec=1;
        ts->tv.tv_usec=0;
        //evtimer_set(&ts->ev_timeout, timeout_cb, ts /*&ev_timeout*/);
        evtimer_add(&ts->ev_timeout, &ts->tv);
    }

}

void conn_input (int sockfd, short event, void* arg)
{
    g_print("%d :conn input %d\n", sockfd, event);

    connection_t *conn = NULL;

    if ( arg ){
        conn = (connection_t *)arg;
    }

    if ( EV_TIMEOUT == event )
    {
        printf("arg is %p, timeout\n", arg);
        event_add (&conn->ev_read, NULL);
    	timeout_add(&conn->ev_read, &conn->tv);
    }

    if ( EV_READ == event)
    {
        printf("arg is %p, read data\n", arg);
        event_add (&conn->ev_read, NULL);
    	timeout_add(&conn->ev_read, &conn->tv);
        evbuffer_read(conn->input, conn->sockfd, 256);
    }

}

void conn_accept (int sockfd, short event, void* arg)
{
    if(event == EV_TIMEOUT)
    {
        g_print("%d :accept timeout %d\n", sockfd, event);
        return;
    }

    g_print("%d :accept %d\n", sockfd, event);
    struct sockaddr_in cliaddr;

    g_print("%s(): fd = %d, event = %d.\n", __func__, sockfd, event);

    socklen_t len = sizeof (struct sockaddr_in);
 
    /* Accept the new connection. */
    int connfd = accept (sockfd, (struct sockaddr*)&cliaddr, &len);
    if (connfd < 0)
    {
        g_print("accept failed! (%s)\n", strerror(errno));
        return;
    }

    connection_t *conn = conn_new(); 

    conn->sockfd = connfd;

    conn->tv.tv_sec = 5;
    //timeout_set(&conn->ev_read, timeout_cb, conn);
    event_set(&conn->ev_read, connfd, EV_READ, conn_input, conn);
    if (event_add (&conn->ev_read, NULL) == -1)
    {
        return;
    }

    timeout_add(&conn->ev_read, &conn->tv);

    g_print("Accepted connection from %s, socket=%d\n",
            inet_ntoa(cliaddr.sin_addr), connfd);
}


int main ()
{
    struct event ev_accept;

    g_print("server_proc_main init .\n");

    int listenfd = create_socket( NULL, 9009, SOCK_STREAM);
    if (listenfd < 0)
    {
        g_print("tcp_listen failed!\n");
        return -1;
    }	

    g_print("listenfd is %d\n", listenfd);
    // initialize libevent.
    event_init ();

    /* We now have a listeing socket, we create a read event to
     * be notified when a client connects. */
    time_slot_t *ts = (time_slot_t *)calloc(1,sizeof(time_slot_t));

    ts->tv.tv_sec=1;
    ts->tv.tv_usec=0;
    evtimer_set(&ts->ev_timeout, timeout_cb, ts /*&ev_timeout*/);
    evtimer_add(&ts->ev_timeout, &ts->tv);
    
    event_set (&ev_accept, listenfd, EV_READ | EV_PERSIST,
               conn_accept, NULL);

    struct timeval tvaccept;
    tvaccept.tv_sec=3;
    tvaccept.tv_usec=3;

    event_add (&ev_accept, &tvaccept);

    
    event_dispatch ();

    return 0;
}

