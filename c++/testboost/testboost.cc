#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <tr1/array>

struct mp
{
	mp(int v):value(v){}
	
	int value;
};

int main()
{
	//std::vector<boost::shared_ptr<int> > int_pool(10);
	std::tr1::array<boost::shared_ptr<mp>,10 > int_pool;

	std::cout<<int_pool.size()<<" "<<int_pool.max_size() << std::endl;

	for (int i=0; i<10; i++)
	{
		boost::shared_ptr<mp> temp(new mp(i+1));
		int_pool[i] = temp;
	}

	std::cout<<int_pool.size()<<" "<<int_pool.max_size() << std::endl;

 	BOOST_FOREACH(boost::shared_ptr<mp> i, int_pool)
  	{
    	std::cout<<i->value<<std::endl;
  	}

	return 0;
}
