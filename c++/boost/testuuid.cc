/*
 * =============================================================================
 *
 *       Filename:  testuuid.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012��06��21�� 16ʱ13��11��
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
    // Nil������(����һ��ȫ��/��Ч��UUID/is_nil)
    uuid nilUUID1 = nil_generator()();          // ��һ�������ǹ��캯��,�ڶ����ǵ������ز�����(operator())
    uuid nilUUID2 = nil_uuid();                 // ��������
    cout<< "nilUUID1: "<<nilUUID1<<endl;
    cout<< "nilUUID2: "<<nilUUID2<<endl;
}
