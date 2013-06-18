#include <stdio.h>

void test()
{
    int x = 4;
    int y = 5;
    auto z = [=]() mutable{x = 3;++y; int w = x + y; return w; };
    z();
    z();
    z();
}

void test1()
{
    int x = 4;
    int y = 5;
    [&](){x = 2;y = 2;}();
    [=]() mutable{x = 3;y = 5;}();
    [=,&x]() mutable{x = 7;y = 9;}();
}

int main()
{
    test();
    test1();
    return 0;    
}

