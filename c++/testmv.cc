#include <iostream>
#include <string>

using namespace std;

class Base
{
  public:
    virtual string name(){return "base";}
};

class Child: public Base
{
  public:
    virtual string name(){return "child";}
};

class IPool
{
public:
   virtual Base* getobj() = 0;
};

class Pool : public IPool {
public:
  Base* getobj(){ return &m_c;}

  Child m_c;
};

int main()
{
  Base* pb = new Child();
  cout<<"new to base: "<<pb->name()<<endl;

  Child c;
  Base *pc = &c;
  Child *d = (Child *)pc;
  cout<<"obj to child: "<<d->name()<<endl;
  
  Pool pool;
  IPool* pp = &pool;
  Child* pe = (Child *)pp->getobj();
  cout<<"obj factory to child: "<<pe->name()<<endl;

  return 0;
}
