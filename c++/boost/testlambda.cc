#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/ref.hpp>
#include <list>
#include <algorithm>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include "testlambda.hpp"

using namespace boost;
int add(int n)
{
    return n+1;
}

class A {
    int i; 
    mutable int j;
public:
    A(int ii, int jj) 
	:i(ii), j(jj) {};
  
    void set_i(int x) { i = x; }; 
    
    void set_j(int x) const { j = x; }; 
};

template<class T>
list<shared_ptr<B<T> > > B<T>::blist_;

template<class T>
ostream & operator<<(ostream &os, const B<T>& b )
{
    os<<"B<T>(";
	os<<b.id_;
    os<<")";
    return os;
}


int main()
{
    list<int> v(10);
    int i=0;
    for_each(v.begin(), v.end(), _1 = 1);
    cout<<v<<endl;

    for_each(v.begin(), v.end(), _1 = bind(add,_1));
    cout<<v<<endl;

    for_each(v.begin(), v.end(), cout<<_1);
    cout<<endl;
	
    A a(0,0); 
    int k = 1;

    bind(&A::set_i, boost::ref(a), _1)(k);
    bind(&A::set_j, a, _1)(k);

    i = 20; 
    int j;
    for_each(v.begin(), v.end(), ( var(j) = 100 )); 	
    cout<<i<<endl;
    cout<<j<<endl;

    int index=0;
    for_each(v.begin(), v.end(), (cout << ++var(index) << ':' << _1 << ';'));
    cout << endl;

	cout<<"begin test lambda"<<endl;
	//list<shared_ptr<B<int> > > blist;

 	try 
	{  
		int c = lexical_cast<int>("wrong number");  
	}  
	catch(bad_lexical_cast & e)  
	{  
	    printf("%s\r\n", e.what());  
	}  

	shared_ptr<B<int> > pb1;

	for(i=0; i<10; ++i)
	{
		shared_ptr<B<int> > pb(new B<int>(lexical_cast<std::string>(i) ));
		pb->start();
		if ( 4 == i)
			pb1 = pb;
	}

	cout<<*pb1<<endl;	
	pb1->stop();

    return 0;
}

