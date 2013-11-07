#include <inttypes.h>
#include <stdlib.h>
#include <thread>
#include <atomic>
#include <iostream>

using namespace std;

//volatile uint64_t value=0;
uint64_t value=0;

atomic<uint64_t> atomicvalue(0);

void counter(int id)
{
    uint64_t previous = 0, updated;

    for (;;) {
        // updated = ++value;
        updated = atomicvalue.fetch_add(1,std::memory_order_relaxed)+1;    

        if (previous >= updated) {
            cerr<<previous<<">="<<updated<<endl;
            exit(EXIT_FAILURE);
        }
        
        previous = updated;
    }
}

void monitor(uint64_t max)
{
    while(1)
    {
        ::sched_yield();
        uint64_t c=atomicvalue.load(std::memory_order_acquire);
        if (c >= max)
        {
            cout<<"c="<<c<<endl;
            break;
        }
    }
}

int
main(int argc, char *argv[])
{
  thread c1(counter, 1);
  thread c2(counter, 2);
  thread c3(counter, 3);
  thread c4(counter, 4);
  thread m1(monitor, 100000000);

  m1.join();

  return 0;
}