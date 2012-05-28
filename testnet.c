#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdint.h>

int main()
{
	char buf[16]="210.25.132.181";
	char buf1[16];

	struct in_addr inp;
	inet_pton(AF_INET, buf, &inp);
	uint32_t ip = ntohl(inp.s_addr);

	printf("%s -> %u\n", buf, ip);
	
	inp.s_addr = htonl(ip);
	char *sip = inet_ntop(AF_INET, &inp, buf1, 16);
		
	printf("%u -> %s\n", ip, buf1);

	return 0;
}
