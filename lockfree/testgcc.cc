#include <stdio.h>
#include <iostream>
#include <thread> 
#include <mutex> 

/*
compile&link: g++ -o tr testgcc.cc -std=c++11 -Wl,--no-as-needed -pthread
*/
using namespace std;

int g_value=0;

static void * counter(int id)
{


  // int oldvalue = __atomic_test_and_set(&g_value, __ATOMIC_RELAXED);//set to 1
  // printf( "TAS:g_value=%d, oldvalue=%d\n", g_value, oldvalue);  

  int oldvalue = __sync_fetch_and_add(&g_value, 1);
  printf( "FAA:ID=%d, g_value=%d, oldvalue=%d\n",id, g_value, oldvalue );

  // oldvalue = __atomic_test_and_set(&g_value, __ATOMIC_RELAXED); //set to 1
  // printf( "TAS:g_value=%d, oldvalue=%d\n", g_value, oldvalue);  

  return (NULL);
}

int main()
{
  char buff[]="hello world!";
  printf("%s\n", buff);

  thread t1(counter, 1);
  thread t2(counter, 2);
  thread t3(counter, 3);
  t1.join();
  t2.join();
  t3.join();

  thread t100([=]{ std::cout << "hello " << buff << std::endl; });
  t100.join();     

  return 0;
}
