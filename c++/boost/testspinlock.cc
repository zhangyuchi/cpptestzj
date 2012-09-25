/*
 * =============================================================================
 *
 *       Filename:  testspinlock.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月23日 10时48分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <boost/thread/shared_mutex.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp> 
#include <stdio.h>

int main()
{
    boost::detail::spinlock s;
    //boost::lock_guard<boost::detail::spinlock> Lock(s);
    boost::detail::spinlock::scoped_lock Lock(s);

    printf("hello world\n");    
    //s.lock();
    //access data structure here
    //s.unlock();
}

