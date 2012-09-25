/*
 * =============================================================================
 *
 *       Filename:  testcpu.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月17日 18时35分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */


#include<stdio.h>
#include<unistd.h>

int main()
{
    int cpu_num;


    cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    printf("_SC_NPROCESSORS_CONF=%d\n",cpu_num);

    cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
    printf("_SC_NPROCESSORS_ONLN=%d\n",cpu_num);


    return 0;
}
