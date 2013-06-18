#include <iostream>
#include <string>

using namespace std;

constexpr int Fib(int n)
{
    return n<=2 ? 1 : Fib(n-1)+Fib(n-2);
}

template<class T, class U>
auto add(T x, U y) -> decltype(x+y)
{
    return x+y;
}


int main()
{
    cout << Fib(25) << endl;

    //int a = 15;
    //cout<<Fib(a);

    uint8_t *p = nullptr;

    string test=R"(C:\A\B\C\D\file1.txt)";
    cout << test << endl;

    cout << add(1,1L) <<endl;    

    return 0;
}

