#include <thread>
#include <mutex>
#include <stdio.h>
#include <unistd.h>

std::mutex m1,m2;
int c1=0;
int c2=0;

void f1()
{
    printf("f1 begin:%d,%d\n", c1, c2);
    std::lock_guard lock1(m1);
    for(int i=0; i<1000000000;++i)
        ++c1;
    sleep(1);
    std::lock_guard lock2(m2);
    ++c2;
    printf("f1 done:%d,%d\n", c1, c2);
}

int main() {
    std::thread t1(f1);
    {
        std::lock_guard lock2(m2);
        for(int i=0; i<100000000;++i)
            ++c2;
        sleep(1);
        std::lock_guard lock1(m1);
        ++c1;        
    }
    t1.join();
    printf("main done:%d,%d\n", c1,c2);
    return 0;
}