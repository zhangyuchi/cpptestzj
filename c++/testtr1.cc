// compile with: /EHsc 
#include <tr1/functional>
#include <algorithm>
#include <iostream>
#include <tr1/tuple>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
 
using namespace std::tr1::placeholders;
using std::cout;
using std::endl;
using std::for_each;
using std::tr1::bind;
using boost::tie;
using boost::tuple;
using std::string;
  
void square(double x)
{
	cout << x << "^2 == " << x * x << endl;
}
  
void product(double x, double y)
{
    cout << x << "*" << y << " == " << x * y << endl;
}
  
tuple<int,int,int> get_tuple()
{
	return boost::make_tuple(1,2,3);
	//return tie(1,2,3);
}

int main() 
{
    double arg[] = {1, 2, 3};
 
    for_each(&arg[0], &arg[3], square);
	cout << endl;
    
	for_each(&arg[0], &arg[3], bind(product, _1, 2) );
	cout << endl;  

	for_each(&arg[0], &arg[3], bind(square, _1) );  

	int i1,i2,i3;
	tie(i1,i2,i3) = get_tuple();	
	
	cout<<i1<<i2<<i3<<endl;

	tuple<float, int, string> a(1.0f,  2, string("Howdy folks!"));
	cout<<a<<endl;

	return 0;
}

