/*
 * =============================================================================
 *
 *       Filename:  testcast.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月24日 15时12分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <boost/lexical_cast.hpp>

int main()
{
    std::string num;
    uint8_t n = 48;

    num.assign((char *)&n, 1);

    int8_t a = boost::lexical_cast<int8_t>("0");  
    int b = boost::lexical_cast<int>("1");  

    printf("a = %d, b = %d\n", a, b);

    return 0;
}

