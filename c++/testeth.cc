#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <stdbool.h>
#include <pwd.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <ifaddrs.h>
#include <net/if.h>

#include <cstdio>
#include <string>
#include <iostream>

std::string get_eth_ip()
{
    struct ifaddrs *ifap;
    if (0 != getifaddrs(&ifap)) {
        std::cerr<<"err = "<<strerror(errno);
        return ""; 
    }   
    
    std::string ethip = "";

    for (struct ifaddrs *ifa = ifap; ifa; ifa = ifa->ifa_next) 
    {   
        if ( strstr(ifa->ifa_name, "eth") && NULL != ifa->ifa_netmask )
        {   
            sockaddr *s=ifa->ifa_addr;
            char sip[32];
            snprintf(sip, 31, "%hhu.%hhu.%hhu.%hhu ", s->sa_data[2],s->sa_data[3],s->sa_data[4],s->sa_data[5]);
            //printf("%s: %hhu.%hhu.%hhu.%hhu", ifa->ifa_name, s->sa_data[2],s->sa_data[3],s->sa_data[4],s->sa_data[5]);
            printf("%s sa_data: %hhu-%hhu-%hhu-%hhu-%hhu-%hhu\n", ifa->ifa_name, s->sa_data[0], s->sa_data[1], s->sa_data[2],s->sa_data[3],s->sa_data[4],s->sa_data[5]);
            ethip.append(sip);
        }   
    }   
   
   	freeifaddrs(ifap); 	

    return ethip;
}

int main(int argc, char** argv)
{
    std::cout<<get_eth_ip()<<std::endl;

    return 0;
}

