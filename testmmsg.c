#define _GNU_SOURCE
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/net.h>

int
main(void)
{
  int sockfd;
  struct sockaddr_in sa[2];
  struct mmsghdr msg[2];
  struct iovec msg1[2], msg2;
  int retval;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket()");
    exit(EXIT_FAILURE);
  }

  sa[0].sin_family = AF_INET;
  sa[0].sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sa[0].sin_port = htons(1234);

  sa[1].sin_family = AF_INET;
  sa[1].sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sa[1].sin_port = htons(4321);


#if 0  
  if (connect(sockfd, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
    perror("connect()");
    exit(EXIT_FAILURE);
  }
#endif

  memset(msg1, 0, sizeof(msg1));
  msg1[0].iov_base = "one";
  msg1[0].iov_len = 3;
  msg1[1].iov_base = "two";
  msg1[1].iov_len = 3;

  memset(&msg2, 0, sizeof(msg2));
  msg2.iov_base = "three";
  msg2.iov_len = 5;

  memset(msg, 0, sizeof(msg));
  msg[0].msg_hdr.msg_name = &sa[0];
  msg[0].msg_hdr.msg_namelen = sizeof(struct sockaddr_in);
  msg[0].msg_hdr.msg_iov = msg1;
  msg[0].msg_hdr.msg_iovlen = 2;

  msg[1].msg_hdr.msg_name = &sa[1];
  msg[1].msg_hdr.msg_namelen = sizeof(struct sockaddr_in);
  msg[1].msg_hdr.msg_iov = &msg2;
  msg[1].msg_hdr.msg_iovlen = 1;

#if 1
  //retval = syscall(SYS_SENDMMSG, sockfd, msg, 2, 0);
  retval = syscall(__NR_sendmmsg, sockfd, msg, 2, 0);
  if (retval == -1)
    perror("sendmmsg()");
  else
    printf("%d messages sent\n", retval);
#else
  retval = sendmsg(sockfd, &msg[0].msg_hdr, 0);
  if (retval == -1)
    perror("sendmsg()");
  else
    printf("%d messages sent\n", retval);
#endif

  exit(0);
}

