#include <iostream>
#include <vector>
#include <boost/foreach.hpp>

using namespace std;

template <typename T>
void print_vector(const vector<T> &v)
{
	BOOST_FOREACH(T i, v)
    {
        cout<<i<<" ";
    } 

	cout<<endl;
}

int main()
{
	vector<int> Iv;

	for(int i = 0; i<10; i++)
	{
		Iv.push_back(i);
	}

	print_vector(Iv);

	remove (Iv.begin(), Iv.end(), 5); 

	print_vector(Iv);

	cout<<"done"<<endl;

	return 0;
}
