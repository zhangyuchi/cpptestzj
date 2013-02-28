#include <iostream>

#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/foreach.hpp>

typedef boost::coroutines::coroutine< int(int,int) > coro_t;

void fn( coro_t::caller_type & ca)
{
    int a, b;
    std::cout << "fn(): 1" << std::endl;
    boost::tie( a, b) = ca.get();
    std::cout << "fn(): 2" << std::endl;
    boost::tie( a, b) = ca( a + b).get();
    std::cout << "fn(): 3" << std::endl;
    ca( a + b);
    std::cout << "fn(): 4" << std::endl;
}

int main( int argc, char * argv[])
{
    std::cout << "main(): call coroutine c" << std::endl;
    coro_t coro( fn, coro_t::arguments( 3, 7) );

    std::cout << "main(): before coro.get" << std::endl;
    BOOST_ASSERT( coro);
    int res = coro.get();
    std::cout << "main(): 3 + 7 == " << res << std::endl;

    res = coro( 5, 7).get();
    BOOST_ASSERT( coro);
    std::cout << "main(): 5 + 7 == " << res << std::endl;
    coro(0,0);

    std::cout << "Done" << std::endl;

    return EXIT_SUCCESS;
}
