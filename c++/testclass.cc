#include <iostream>
using namespace std;

class Base
{
public:
  virtual int name(){cout<<"Base"<<endl;}
  int go(){cout<<"go "<<endl;}
};

class Derived : public Base
{
public:
  int name(){cout<<"Derived"<<endl;}    
  int go(int feet){cout<<"go "<<feet<<" feet!"<<endl;}
};


int main()
{
  Base b;
  Derived d;

  b.name();
  b.go();  
  d.name();
  d.go();

  Derived* pd = new Derived();
  Base* pb = pd;

  pb->name();
  pb->go();
  pd->name();
  pd->go();

  return 0;
}
