#include <iostream>

#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>

typedef boost::coroutines::coroutine< void() > coro_t;

// void fn( boost::coroutines::coroutine< void() > & ca, int j)
void fn( coro_t::caller_type & ca, int j)
{
    for( int i = 0; i < j; ++i)
    {
        std::cout << "fn(): local variable i == " << i << std::endl;

        // save current coroutine
        // value of local variable is preserved
        // transfer execution control back to main()
        ca();

        std::cout<<  "fn(): continue"<<std::endl;
        
        // coroutine<>::operator()() was called
        // execution control transferred back from main()
    }
}

int main( int argc, char * argv[])
{
    // bind parameter '7' to coroutine-fn
    coro_t c( boost::bind( fn, _1, 7) );

    std::cout << "main() starts coroutine c" << std::endl;

    while ( c)
    {
        std::cout << "main() calls coroutine c" << std::endl;
        // execution control is transferred to c
        c();
    }

    std::cout << "Done" << std::endl;

    return EXIT_SUCCESS;
}

