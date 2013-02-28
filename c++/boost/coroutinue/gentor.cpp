#include <iostream>

#include <boost/bind.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/foreach.hpp>

typedef boost::coroutines::coroutine< int() >       coro_t;
typedef boost::range_iterator< coro_t >::type       iterator_t;

void power( coro_t::caller_type & ca, int number, int exponent)
{
    int counter = 0;
    int result = 1;
    while ( counter++ < exponent)
    {
        result = result * number;
        ca( result);
    }
}

int main()
{
    coro_t c( boost::bind( power, _1, 2, 8) );
    iterator_t e( boost::end( c) );
    for ( iterator_t i( boost::begin( c) ); i != e; ++i)
        std::cout << * i <<  " ";

    std::cout << "\nDone" << std::endl;

    return EXIT_SUCCESS;
}

