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

int main()
{
    test();
    return 0;    
}

