/*
 * =============================================================================
 *
 *       Filename:  testmemory.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012��09��05�� 15ʱ53��00��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    void *data = calloc(1,16);

    memcpy(data, "\x12\x34\x56\x78", 4);

    printf("id = 0x%x\n", *(int *)data);
    return 0;
}
