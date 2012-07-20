/*
 * =============================================================================
 *
 *       Filename:  testuuid.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月21日 16时13分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <vector>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost::uuids;
using namespace std;
int main()
{
    // Nil生成器(生成一个全零/无效的UUID/is_nil)
    uuid nilUUID1 = nil_generator()();          // 第一个括号是构造函数,第二个是调用重载操作符(operator())
    uuid nilUUID2 = nil_uuid();                 // 内联函数
    cout<< "nilUUID1: "<<nilUUID1<<endl;
    cout<< "nilUUID2: "<<nilUUID2<<endl;
}
