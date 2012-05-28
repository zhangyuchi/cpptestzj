#include <czmq.h>

int main()
{
	zsocket_test (TRUE);
	zmsg_test(TRUE);
	zframe_test (TRUE);

	return 0;
}

