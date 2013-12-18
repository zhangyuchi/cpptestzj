#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> f(0);
int a;

void func1()
{
    for (int i = 0; i<1000000; ++i) {
        a = i;
        atomic_thread_fence(std::memory_order_release);
        f.store(i, std::memory_order_relaxed);
    }
}

void func2()
{
    int prev_val = 0;
    while (prev_val < 1000000) {
        while (true) {
            int new_val = f.load(std::memory_order_relaxed);
            if (prev_val < new_val) {
                prev_val = new_val;
                break;
            }
        }

        atomic_thread_fence(std::memory_order_acquire);
        std::cout << a << ' ';//cann't print all a form 0-999999
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    std::thread c1(func1);
    std::thread c2(func2);

    c1.join();
    std::cout<<"c1 end"<<std::endl;
    c2.join();
    std::cout<<"c2 end"<<std::endl;

    return 0;
}