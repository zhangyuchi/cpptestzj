#include <boost/asio/buffer.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using boost::asio::buffer;
using boost::asio::mutable_buffer;
using boost::asio::const_buffer;

int main()
{
	mutable_buffer mb;
	const_buffer cb;

	{
		char a[]="hello";

		mb = buffer(a, strlen(a));
		cb = buffer(a, strlen(a));
		
		cout<<"og: "<<(void *)a<<a<<endl;
		cout<<"mb: "<<boost::asio::detail::buffer_cast_helper(mb)<<static_cast<char *>(boost::asio::detail::buffer_cast_helper(mb))<<endl;
		cout<<"cb: "<<boost::asio::detail::buffer_cast_helper(cb)<<static_cast<const char *>(boost::asio::detail::buffer_cast_helper(cb))<<endl;
	}

	char b[]="world";
	cout<<"og: "<<(void *)b<<b<<endl;
	cout<<"mb: "<<boost::asio::detail::buffer_cast_helper(mb)<<static_cast<char *>(boost::asio::detail::buffer_cast_helper(mb))<<endl;
	cout<<"cb: "<<boost::asio::detail::buffer_cast_helper(cb)<<static_cast<const char *>(boost::asio::detail::buffer_cast_helper(cb))<<endl;
	return 0;
}

