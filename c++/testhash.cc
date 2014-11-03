/*
 * =============================================================================
 *
 *       Filename:  testhash.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月11日 17时01分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <string>
#include <tr1/unordered_map>
#include <iostream>
#include "portable.h"

using namespace std;
using namespace std::tr1;

int main()
{
    hash<string> hasher;

    string s = "heyho";

    size_t hash = hasher(s);

    cout<<hash<<endl;
    
    cout<<"gcc ver="<<__GNUC__<<endl;

    return 0;
}
