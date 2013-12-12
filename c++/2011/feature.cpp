#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct NoInt {
  auto f(double i) ->double { cout<<"double: "<<i<<endl; return i;}
  int f(int i) { cout<<"int: "<<i<<endl; return i; }
  char* f(char* i) { cout<<"char*: "<<(void *)i<<endl; return i; }
};

struct alignas(8) complex{
  char flag;
  int real;
  int virt;
  float lenght;
};

template <class Lhs, class Rhs>
auto add(const Lhs & lhs, const Rhs & rhs) -> decltype(lhs+rhs) 
{ 
  return lhs + rhs; 
}

int main()
{
  NoInt ni;
  ni.f(14.01);
  ni.f(14);
  ni.f(nullptr);
  //ni.f(NULL); error

  complex c1 = {'b', 1, 234, 257};
  cout<<sizeof(c1)<<endl;
  cout<<alignof(c1)<<endl;
  

  vector<string> test_string = {"Make", "One", "Program", "Do", "One", "Thing", "Well"}; 
  //cout<<test_string<<endl;

  double sum = add(10, 11.42);
  cout<<"sum: "<<sum<<endl;

  return 0;
}

