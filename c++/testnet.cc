/*
 * =============================================================================
 *
 *       Filename:  testnet.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月12日 17时29分20秒
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

int main()
{
    struct ifaddrs *ifap;

    if (0 != getifaddrs(&ifap)) {
        printf("err = %s\n", strerror(errno) );
        return -1;
    }

    for (struct ifaddrs *ifa = ifap; ifa; ifa = ifa->ifa_next) 
    {

        if ( !strcmp(ifa->ifa_name, "eth0") &&  NULL != ifa->ifa_netmask )
        {
            sockaddr *s=ifa->ifa_addr;
            printf("%s %u sockaddr %hhu.%hhu.%hhu.%hhu \n", ifa->ifa_name, ifa->ifa_flags, s->sa_data[2],s->sa_data[3],s->sa_data[4],s->sa_data[5]);
        }
    }
   
      freeifaddrs(ifap); 

    return 0;
}
