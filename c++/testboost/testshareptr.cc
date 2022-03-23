#include <list>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using namespace boost::lambda;

class session
{
public:
	session(int id):id_(id){}
	
	bool operator == (const session& other) const
	{
		return this->id_ == other.id_;
	}

	bool operator == (int v) const
    {
        return this->id_ == v;
    }

	int id_;
};

template <typename T>
void print_list(std::list<T>& inputlist)
{
	typename std::list<T>::iterator it;
	for (it=inputlist.begin(); it!=inputlist.end(); ++it)
    	std::cout << " " << (*it)->id_;
  
	std::cout << std::endl;
}

int main()
{
	std::list<boost::shared_ptr<session> > session_list;

	for ( int i=0; i<10; i++ )
	{
		boost::shared_ptr<session> ps(new session(i));
		session_list.push_back(ps);
	}

	print_list(session_list);

	session_list.remove_if(*_1==4); 
	
	print_list(session_list);
	return 0;
}

