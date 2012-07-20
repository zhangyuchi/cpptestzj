/*
 * =============================================================================
 *
 *       Filename:  testrandom.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月21日 13时56分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <iostream>
#include <cmath>
#include "random.h"

int main()
{
    Random ran;
   
    std::cout<<(pow(2,63))<<std::endl;    

    for(int i=0; i<100; ++i)
    {
       std::cout << ran.get() << " ";
    }

    std::cout<<std::endl;
    return 0;
}

