/*
 * =============================================================================
 *
 *       Filename:  teststralgo.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月21日 16时42分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <string>
#include <iostream>
#include <iterator>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/foreach.hpp>
#include <vector>


using namespace std;
using namespace boost;
int main()
{  
    string str = "abc==1234def>=ijkl<=mnop56qrs>tuv7890=wxyz" ;
    vector< string > result;
    boost::algorithm::split_regex( result, str, 
            regex( "[><=]+=|[><]+" ) ) ;

 	BOOST_FOREACH(string i, result)
  	{
    	cout<<i<<endl;
  	}

    return 0;
}

