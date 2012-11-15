/*
 * =============================================================================
 *
 *       Filename:  teststatic.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012��10��12�� 14ʱ26��40��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <iostream>
using namespace std;

template<typename T>
class Connect
{
public:
    void init()
    {
        cout<<++number<<endl;
    }

    void stop()
    {
        cout<<--number<<endl;
    }
private:
    static int number;
    T v;
};

template<typename T> int Connect<T>::number=0;

