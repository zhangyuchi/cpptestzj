#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Foo {
  void foo() & { std::cout << "lvalue" << std::endl; }
  void foo() && { std::cout << "rvalue" << std::endl; }
};


struct Test {
  int num=1000;
  void func() {cout<<"Test::func"<<endl;}
};

struct Number {
  Number &operator ++ (); // Generate a prefix ++ operator
  Number operator ++ (int); // Generate a postfix ++ operator
};

// Notice the extra "Test::" in the pointer type
int Test::*ptr_num = &Test::num;
void (Test::*ptr_func)() = &Test::func;

namespace __hidden__ {
  struct print {
    bool space;
    print() : space(false) {}
    ~print() { std::cout << std::endl; }

    template <typename T>
      print &operator , (const T &t) {
        if (space) std::cout << ' ';
        else space = true;
        std::cout << t;
        return *this;
                                                          }
      };
}

#define print __hidden__::print(),

template <int (*f)(int)>
int memoize(int x) {
  static std::map<int, int> cache;
  std::map<int, int>::iterator y = cache.find(x);
  if (y != cache.end()) 
    return y->second;
  return cache[x] = f(x);
}

int fib(int n) {
  if (n < 2) return n;
    return memoize<fib>(n - 1) + memoize<fib>(n - 2);
}

template <typename T>
struct Cache {  };

template <typename T>
struct NetworkStore {  };

template <typename T>
struct MemoryStore {  };

template <template <typename> class Store, typename T>
struct CachedStore {
  Store<T> store;
  Cache<T> cache;
};

struct B {
  int b;
  B() try : b(fib(6)) 
  {
    cout<<"normal B"<<endl;
  } 
  catch(int e) 
  {
    cout<<"exception B"<<endl;
  }
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

  Test t;
  Test *pt = new Test;

  // Call the stored member function
  (t.*ptr_func)();
  (pt->*ptr_func)();
    
  // Set the variable in the stored member slot
  t.*ptr_num = 1;
  pt->*ptr_num = 2;
  delete pt;

  std::cout << sizeof(void (Test::*)()) << std::endl;

  int a = 1, b = 2;
  print "this is a test";
  print "the sum of", a, "and", b, "is", a + b;

  print "fib(5) is", fib(15);

  CachedStore<NetworkStore, int> netcache;
  CachedStore<MemoryStore, int>  memcache;

  return 0;
}

