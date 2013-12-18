#include <atomic>
#include <thread>
#include <iostream>
#include <cassert>

using namespace std;

atomic<int> x(0);
int y=0;

void func1()
{
  y = 20;
  x.store (10, memory_order_relaxed);
}

void func2()
{
  cout<<x.load(memory_order_relaxed)<<" ";
  cout<<y<<endl;
}

int main(int argc, char const *argv[])
{
  while(1)
  {
    std::thread c2(func2);
    std::thread c1(func1);

    c1.join();
    c2.join();
  }

  /* code */
  return 0;
}
