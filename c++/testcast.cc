#include <iostream>

using namespace std;

int main()
{
	int n=9;
	//double d = reinterpret_cast<double> (n);
	double d = static_cast<double> (n);
	long l = static_cast<long> (n);
	
	cout << n << " -> " << d << " -> " << l << endl;
	
	return 0;
}

