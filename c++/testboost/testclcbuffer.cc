/*
 * =============================================================================
 *
 *       Filename:  testclcbuffer.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月20日 15时46分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <stdint.h>
#include <vector>
#include <boost/circular_buffer.hpp>

int main()
{
    uint8_t lbuf[] = "hello";

    boost::circular_buffer<std::vector<uint8_t> > cmd_cache;

    std::vector<uint8_t> buffer;
    buffer.insert(buffer.end(), lbuf, lbuf+5);

    cmd_cache.push_back(buffer);

    return 0;
}


