#include <stdint.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;

typedef map<int,string> IS;

int main()
{
  IS mapis;
  mapis.insert(pair<int,string>(1,"chi"));
  mapis.insert(pair<int,string>(2,89));

  cout<<"1:"<<mapis[1]<<endl;
  cout<<"2:"<<mapis[2]<<endl;

  return 0;
}
