#include <iostream>
#include <thread> 
#include <atomic>

using namespace std;

atomic<int> x,y;

void run1(){
  x.store(1,std::memory_order_release);
  // cout<<"run1: x="<<x<<endl;
}

void run2(){
  y.store(1,std::memory_order_release); 
  // cout<<"run2: y="<<y<<endl;
}

void run3(){
  int a=x.load(std::memory_order_acquire); // x before y
  int b=y.load(std::memory_order_acquire); 

  cout<<"run3: a="<<a<<";b="<<b<<endl;
}

void run4(){
  int c=y.load(std::memory_order_acquire); // y before x
  int d=x.load(std::memory_order_acquire);  

  // cout<<"run4: c="<<c<<";d="<<d<<endl;  
}

int main()
{
  while(1){
    thread t1(run1);
    thread t2(run2);
    thread t3(run3);
    thread t4(run4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
  
  return 0;
}