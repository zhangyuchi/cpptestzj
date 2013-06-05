#include <iostream>
#include <future>

using namespace std;

int Fib(int n){
    return n<=2 ? 1 : Fib(n-1)+Fib(n-2);
}

int calc1(){ return Fib(30); }

int calc2(){ return Fib(40); }

int main()
{
    // start calc1() asynchronously
    future<int> result1 = async(calc1);
    // // call calc2() synchronously
    int result2 = calc2();
    // // wait for calc1() and add its result to result2
    int result = result1.get() + result2;
    cout << "calc1()+calc2(): " << result << endl;
    return 0;
}

