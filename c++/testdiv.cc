/*
 * =============================================================================
 *
 *       Filename:  testdiv.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月25日 16时14分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <stdio.h>
#include <vector>

int main()
{
    std::size_t vnode_num = 32;
    std::size_t rnode_num = 2;    
    std::size_t section_num = vnode_num/rnode_num;

    std::size_t section_id = 16/section_num;

    printf("section_id = %lu\n", section_id);

    return 0;
}

