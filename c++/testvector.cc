#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include <string.h>
#include <cstdio>

using namespace std;

template <typename T>
void print_vector(const vector<T> &v)
{
    cout<<v.size()<<endl;
	BOOST_FOREACH(T i, v)
    {
        cout<<i<<" ";
    } 

	cout<<endl;
}

void print_vector(const vector<unsigned char> &v)
{
    printf("%d\n", v.size());
	BOOST_FOREACH(unsigned char i, v)
    {
        printf("%d-%c ", i,i);
    } 

	cout<<endl;
}

int main()
{
    std::cout<<"------------------------------------------------------"<<std::endl;
	vector<int> Iv;

	for(int i = 0; i<10; i++)
	{
		Iv.push_back(i);
	}

	print_vector(Iv);

	remove (Iv.begin(), Iv.end(), 5); 

	print_vector(Iv);

	cout<<"done"<<endl;
    std::cout<<"------------------------------------------------------"<<std::endl;

    unsigned char* buf = (unsigned char *)"0123456789";
    vector<unsigned char> *pvstr = new vector<unsigned char>();
    int len = 16;
    buf = (unsigned char *)&len;
    pvstr->insert(pvstr->end(), buf, buf+4);
    pvstr->insert(pvstr->end(), buf+4, buf+7);
    pvstr->insert(pvstr->end(), buf+7, buf+10);
    print_vector(*pvstr);

    len = 32;
    memcpy(&(*pvstr)[4], &len,4);
    print_vector(*pvstr);

    std::vector<uint8_t> ka;
    uint8_t kamsg[] = "keepalive";
    ka.insert(ka.begin(), kamsg, kamsg+strlen((char *)kamsg));
    print_vector(ka);

	return 0;
}
