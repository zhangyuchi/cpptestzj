#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string name = "zj";	
	ostringstream s;
	s << "hello " << name << " world" << endl;

	cout << s.str();	

	return 0;
}

