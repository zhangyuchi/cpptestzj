#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/scope_exit.hpp>

using namespace std;

struct Lock
{
  Lock(){ cout<<"Lock"<<endl; }
  ~Lock(){ cout<<"~Lock"<<endl; }
};

void testscope()
{
  for (int i=0; i<10; ++i)
  {
    Lock* lock = NULL;
    Lock* lock1 = new Lock();
    boost::scoped_ptr<Lock> sp(lock);
    boost::scoped_ptr<Lock> sp1(lock1);
    //boost::scoped_ptr<Lock> sp2(lock2);
  }
}

void testptrc()
{
  boost::ptr_map<int,Lock> locks;

  for (int i=0; i<10; ++i)
  {
    locks.insert(i, new Lock());
  }
  
  size_t size = locks.erase(5);  
  cout<<"erase 5, size is "<<size<<endl;

  cout<<"end of ptrc"<<endl;
}

int main(int argc, char** argv)
{
  Lock* tl = new Lock(); 
  BOOST_SCOPE_EXIT(tl) {
  // Whatever happened in scope, this code will be
    delete tl;
  } BOOST_SCOPE_EXIT_END

  if (argc < 2)
  {
    cout<<"scope scope or ptrc"<<endl;
    return -1;
  }

  if ( !strcmp(argv[1], "scope") )
  {
    testscope();
  }

  if ( !strcmp(argv[1], "ptrc") )
  {
    testptrc();
  }

  cout<<"end of main"<<endl;

  return 0;
}

