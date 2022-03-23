#include <iostream>
#include <string>
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"
#include "boost/array.hpp"
#include <stdint.h>


template <typename T> void some_func(
        T t,typename boost::enable_if<
        boost::is_signed<T> >::type* p=0) 
{
    //typename T::type variable_of_nested_type;
    std::cout << "template <typename T> void some_func(signed t)\n";
}

template <typename T> void some_func(
        T t,typename boost::enable_if<
        boost::is_unsigned<T> >::type* p=0) 
{
    //typename T::type variable_of_nested_type;
    std::cout << "template <typename T> void some_func(unsigned t)\n";
}

template <typename T> void some_func(
        T t,typename boost::enable_if<
        boost::is_array<T> >::type* p=0) 
{
    //typename T::type variable_of_nested_type;
    std::cout << "template <typename T> void some_func(array t)\n";
}

template <typename T> void some_func(
        T t,typename boost::enable_if<
        boost::is_pointer<T> >::type* p=0) 
{
    //typename T::type variable_of_nested_type;
    std::cout << "template <typename T> void some_func(pointer t)\n";
}

template<typename T, int N>
void some_real_func(T(&var)[N])
{
    typedef T Type[N];
    std::cout << __FUNCTION__  << " [" << typeid( var ).name( ) << "]." << std::endl;
    std::cout << "->    var is ARRAY. Size = " << sizeof( Type ) << std::endl;
    std::cout << "Number of elements: " << N << std::endl;
    std::cout << "Size of each element: " << sizeof(T) << std::endl;
}

void some_real_func(std::string i) {
    std::cout << "void some_func(" << i << ")\n";
}

struct t_test
{
    int id;
};

int main()
{        
    uint8_t  u8=1;
    uint16_t u16=2;
    uint32_t u32=3;
    uint64_t u64=4;
    uint8_t u8s[16];
    int i8s[16];

    int8_t i8=1;

    uint8_t *u8p = 0;

    some_func(u8);
    some_func(u16);
    some_func(u32);
    some_func(u64);

    some_func(i8);

    some_real_func(std::string("df"));
    some_func<int[16]>(i8s);
    some_func(i8s);
    some_func(u8p);
    //some_func(t_test());

    std::cout<<boost::is_array<int[16]>::value<<std::endl; 

    return 0;
}

