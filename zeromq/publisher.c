//
// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates
//
#include "zhelpers.h"

#include <czmq.h>

int main (void)
{
	//zmq api
	//void *context = zmq_init (1);
	//void *publisher = zmq_socket (context, ZMQ_PUB);
	//zmq_bind (publisher, "tcp://*:5556");
	//zmq_connect (publisher, "tcp://localhost:5556");
	//zmq_connect (publisher, "tcp://localhost:5557");
	
	//czmq api
	zctx_t *ctx = zctx_new();
    //zctx_set_iothreads (ctx, 1);
    zctx_set_linger (ctx, 5);       //  5 msecs
	void *publisher = zsocket_new (ctx, ZMQ_PUB);
	//zsocket_bind (publisher, "tcp://*:5556");
	zsocket_connect (publisher, "tcp://localhost:5556");
	zsocket_connect (publisher, "tcp://localhost:5557");

	//zmq_bind (publisher, "ipc://weather.ipc");

	printf("connect to 5556\n");
	// Initialize random number generator
	srandom ((unsigned) time (NULL));
	int i=0;
	for ( ; i<10; ++i)
	{
		sleep(1);
		// Get values that will fool the boss
		int zipcode, temperature, relhumidity;
		zipcode = 10001;
		temperature = randof (215) - 80;
		relhumidity = randof (50) + 10;

		// Send message to all subscribers
		char update [20];
		char update1 [20];
		printf("send mesg: ");
		zmsg_t *msg = zmsg_new ();
		sprintf (update1, "%d %d", temperature, relhumidity);
		//sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
		zmsg_pushstr(msg, update1);
		sprintf (update, "%05d", zipcode);
		zmsg_pushstr(msg, update);

		printf("msg size is %d\n", zmsg_size(msg));
    	printf("msg content size is %d\n", zmsg_content_size(msg));

		zmsg_send (&msg, publisher);
		printf("%s - %s\n", update, update1);
	}

	zsocket_destroy (ctx, publisher);
	zctx_destroy (&ctx);
	return 0;
}

