#include <iostream>
#include <future>
#include <vector>
#include <algorithm>

using namespace std;

int Fib(int n){
  return n<=2 ? 1 : Fib(n-1)+Fib(n-2);
}

int calc1(){ return Fib(30); }

int calc2(){ return Fib(40); }

void fibtest()
{
  // start calc1() asynchronously
  /*future<int>*/ auto result1 = async(calc1);
  // // call calc2() synchronously
  int result2 = calc2();
  // // wait for calc1() and add its result to result2
  int result = result1.get() + result2;
  cout << "calc1()+calc2(): " << result << endl;
}

int intses()
{
  int i=0;
  return ++i;
}

void parallel_intses()
{
  auto ses = async(std::launch::deferred, intses);
  for(int i=0; i<10; ++i)
    if (ses.valid())
      cout<<ses.get();
  cout<<endl;
}

template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
  auto len = end - beg;
  if(len < 1000)
    return std::accumulate(beg, end, 0);

  RAIter mid = beg + len/2;
  auto handle = std::async(std::launch::async, parallel_sum<RAIter>, mid, end);
  int sum = parallel_sum(beg, mid);
  return sum + handle.get();
}

int main()
{
  //fibtest();
  //parallel_intses();
  std::vector<int> v(1000000, 1);
  std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

  return 0;
}

