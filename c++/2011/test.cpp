#include <iostream>

using namespace std;

constexpr int Fib(int n)
{
    return n<=2 ? 1 : Fib(n-1)+Fib(n-2);
}

int main()
{
    cout << Fib(45) << endl;

    //int a = 15;
    //cout<<Fib(a);

    return 0;
}

