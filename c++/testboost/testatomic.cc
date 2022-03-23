/*
 * =============================================================================
 *
 *       Filename:  testatomic.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月16日 16时29分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

//#include <boost/interprocess/detail/atomic.hpp> 
#include <boost/detail/atomic_count.hpp>
#include <iostream>
#include <stdint.h>
#include <boost/thread.hpp>

int start=0;

/*
int threadrun(boost::detail::atomic_count *base)
{
    for(int i=0; i<10; ++i)
    {
        std::cout<<++(*base)<<std::endl;
    }

    return *base;
}
*/

int threadrun(int *base, int id)
{
    while(1)
    {
        if (start>0)    
        {
            for(int i=0; i<10; ++i)
            {
                std::cout<<id<<": "<<++(*base)<<std::endl;
            }
            break;
        }
        else
            continue;
    }

    return *base;
}

int main()
{
    //boost::atomic<uint64_t> count(1);
    
    //boost::detail::atomic_count count(0);
    int count=0;
    boost::thread *ths[4];

    for(int i=0; i<4; ++i)
    {
        ths[i] = new boost::thread(boost::bind(threadrun, &count, i+1));
    }

    start=1;

    for(int i=0; i<4; ++i)
    {
        ths[i]->join();// = new boost::thread(boost::bind(threadrun<1>, &count));
    }

    return 0;
}

