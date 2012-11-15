/*
 * =============================================================================
 *
 *       Filename:  teststatic.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月12日 14时29分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include "teststatic.h"

int main()
{
    Connect<int> c1;
    c1.init();

    Connect<int> c2;
    c2.init();

    Connect<double> c3;
    c3.init();

    return 0;
}

