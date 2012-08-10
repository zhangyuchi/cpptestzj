/*
 * =============================================================================
 *
 *       Filename:  testbitset.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月07日 18时04分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
using namespace std;

int main ()
{
    int n=16;
    vector<bool> mybits(16, false);
   
    char *buf;

    //bitset<n> mybits;
    mybits[0]=true;
    cout << mybits[0] << endl;      // 1111
    cout << mybits.size()<<endl;

    buf = (char *)&mybits[0];
    
    return 0;
}
