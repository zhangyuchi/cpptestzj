#include <iostream>

using namespace std;

struct Foo {
  void foo() & { std::cout << "lvalue" << std::endl; }
  void foo() && { std::cout << "rvalue" << std::endl; }
};


int main()
{
  cout<<"weird!!!"<<endl;

  int (x) = 3;
  int z = 1;
  int bar(int(y));//function declair, bar is function
  int far((int(x))); //far is var

  cout<<(x and z)<<endl;

  if (int n1 = 1)
    cout<<"n1:"<<n1<<endl;

  if (int n0 = 0)
    cout<<"n0:"<<n0<<endl;

  Foo foo;
  foo.foo(); // Prints "lvalue"
  Foo().foo(); // Prints "rvalue"

  Foo *pfoo = &foo;
  pfoo->foo();

  return 0;
}

