#include <iostream>

using namespace std;

void f()
{
  cout<<"0 args"<<endl;
}
void f(int a)
{
  cout<<"1 args"<<endl;
}
void f(int a, int b)
{
  cout<<"2 args"<<endl;
}
void f(int a, int b, int c)
{
  cout<<"3 args"<<endl;
}

template <int... N>
struct call_impl
{
  static void call()
  {
    f(N...);
  }
};

int main()
{
  call_impl<1,2,3,4>::call();  

  return 0;
}


