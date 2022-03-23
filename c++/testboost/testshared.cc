#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>

using namespace std;

template<typename T>
class D:public boost::enable_shared_from_this<D<T> >
{
public:
	D(T i):id_(i){}

	void func()
    {
    	boost::shared_ptr<D<T> > p=shared_from_this();
    	cout<<p->id()<<endl;
    }

    const T& id() const
    {
    	return id_;
    }

private:
	T id_;
};

int main()
{
	//D d;
	//d.func();

	boost::shared_ptr<D<int> > d(new D<int>(12) );
	d->func();

	return 0;
}

