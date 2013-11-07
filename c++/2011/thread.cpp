#include <iostream> 
#include <thread> 
#include <mutex> 

using namespace std;

mutex m;

void run(size_t n)
{
    m.lock();
    for (size_t i = 0; i < 5; ++i){
        cout << n << ": " << i << endl;
    }
    m.unlock();
}

int main()
{
    thread t1(run, 1);
    thread t2(run, 2);
    thread t3(run, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
