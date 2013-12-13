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

class alignas(8) real {
public:
  real(char flag):flag_(flag){}
  real():real('r'){}

  char flag_ = 'a';
};

class complex : public real {
public:
  using real::real;

  int real_;
  int virt_;
  float lenght_;
};

enum class Color: int32_t { RED = 1, GREEN = 2, BLUE = 3};

template <class Lhs, class Rhs>
auto add(const Lhs & lhs, const Rhs & rhs) -> decltype(lhs+rhs) 
{ 
  return lhs + rhs; 
}

constexpr int MeaningOfLife ( int a, int b ) 
{ 
  return a * b; 
}

int x;

int getInt()
{
  return x;
}

int && getRvalueInt()
{
  //notice that it's fine to move a primitive type--remember, std::move is just a cast
  return move(x);
}

void printAddress(const int & v)
{
  cout << reinterpret_cast<const void*>(&v) << endl;
}

/*
  Variadic templates Args
*/
template<typename T>  
void Print(T&& value)  //this is must exist
{  
  cout << value << endl;  
}  

template<typename Head, typename ... Ts>  
void Print(Head head, Ts... rest) 
{  
  cout<< head <<endl;  
  Print(rest...);
} 

int main()
{
  NoInt ni;
  ni.f(14.01);
  ni.f(14);
  ni.f(nullptr);
  //ni.f(NULL); error

  //complex c1 = {'b', 1, 234, 257};
  complex c1('c');
  cout<<sizeof(c1)<<c1.flag_<<endl;
  cout<<alignof(c1)<<endl;
  

  vector<string> test_strings = {"Make", "One", "Program", "Do", "One", "Thing", "Well"}; 
  for(auto ite : test_strings)
    cout<<ite<<", ";
  cout<<endl;

  double sum = add(10, 11.42);
  cout<<"sum: "<<sum<<endl;

  Color color = Color::GREEN;
  if ( Color::RED == color )
    cout<<"red"<<endl;
  else if ( Color::GREEN == color )
    cout<<"green"<<endl;

  const int meaningOfLife = MeaningOfLife( 6, 7 );
  cout<<"meaningOfLife: "<<meaningOfLife<<endl;

  int *nonull = new int{1};
  const int *p1 = nullptr;
  // constexpr int *p2 = address(mf); //error
  constexpr int *p2 = nullptr; 

  p1 = nonull;
  cout<<"p1: "<<*p1<<endl;
  //*p1 = 2; //error
  cout<<"p2: "<<p2<<endl; 
  //p2 = nonull; //error
  
  static_assert(sizeof(int) <= sizeof(long), "assert"); 

  printAddress(getInt());
  printAddress(x);
  printAddress(getRvalueInt()); //rvalue reference won't happen to copy

  Print(1,2,3,4,p2);

  return 0;
}

