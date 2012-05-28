#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/ref.hpp>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace boost::lambda;

template <typename T>
ostream & operator<<(ostream &os, const list<T>& v )  
{  
	os<<"[";
    BOOST_FOREACH(T i, v)
    {
		os<<i<<",";
    }  

	os<<"]";
    return os;  
} 

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
	for_each(v.begin(), v.end(), (var(j) = _1, _1 = var(i), var(i) = var(j))); 	
	cout<<v<<endl;
	cout<<i<<endl;

	return 0;
}

