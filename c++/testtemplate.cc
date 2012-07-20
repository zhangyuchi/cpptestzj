/*
 * =============================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2012 05:48:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <iostream>
#include <vector>
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"
#include "boost/mpl/has_xxx.hpp"
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)

void f(int &i)
{
    std::cout << "int" << std::endl;
}

template<typename Cont>
typename boost::disable_if<has_iterator<Cont>, void >::type 
f(Cont& c ) 
{
    std::cout << "flat" << std::endl; 
}

template<typename Cont>
typename boost::enable_if<has_iterator<Cont>, void >::type
f(Cont& c) 
{
    std::cout << "container" << std::endl; 
}

void test() 
{
    int a;
    std::vector<int> b;
    float c;
    f(a);
    f(b);
    f(c);
}

int main()
{
    test();
    return 0;
}

