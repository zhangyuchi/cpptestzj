//
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
//
#include "zhelpers.h"

int main (int argc, char *argv [])
{
	void *context = zmq_init (1);

	char *port = (argc > 1)? argv [1]: "5556";

	// Socket to talk to server
	printf ("Collecting updates from weather server¡­\n");
	void *subscriber = zmq_socket (context, ZMQ_SUB);
	char bindaddr[32];
	sprintf(bindaddr, "tcp://*:%s", port);
	zmq_bind (subscriber, bindaddr);
	//zmq_connect (subscriber, bindaddr);

	// Subscribe to zipcode, default is NYC, 10001
	char *filter = "10001";
	printf("filter is %s\n", filter);
	zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));

	// Process 100 updates
	int update_nbr;
	long total_temp = 0;
	printf ("connect to %s server¡­\n", port);
	for ( update_nbr = 0; update_nbr < 100; update_nbr++) 
	{
		printf ("recv mesg: ");
		char *string = s_recv (subscriber);
		printf ("%s\n", string);		
		free (string);

		string = s_recv (subscriber);
		printf ("%s\n", string);		
		free (string);
		//int zipcode, temperature, relhumidity;
		//sscanf (string, "%d %d %d", &zipcode, &temperature, &relhumidity);
		//total_temp += temperature;
	}
	printf ("Average temperature for zipcode '%s' was %dF\n",
	filter, (int) (total_temp / update_nbr));

	zmq_close (subscriber);
	zmq_term (context);
	return 0;
}

