/*
 * =============================================================================
 *
 *       Filename:  testmap.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月25日 16时43分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

struct uin
{
    uin(const std::string& name )
    {
        fullname = name;
        typedef std::vector<std::string> split_vector_type;         
        split_vector_type SplitVec;
        boost::split( SplitVec, fullname, boost::is_any_of("/") );
        basename = SplitVec[0];                        
    }

    std::string basename;
    std::string fullname;

    void print() const
    {
        std::cout<<basename<<std::endl;
        std::cout<<fullname<<std::endl;
        std::cout<<std::endl;
    }
};

int main()
{
    uin id1("zhangjun/pc");
    uin id2("zhangjun/mobile");

    typedef std::multimap<std::string, uin> Uinmap;

    Uinmap uinmap;
    uinmap.insert(make_pair(id1.basename, id1));
    uinmap.insert(make_pair(id1.basename, id1));
    uinmap.insert(make_pair(id1.basename, id1));

    std::multimap<std::string, uin>::iterator uit = uinmap.begin();
    for( ; uit != uinmap.end(); ++uit)
    {
        uit->second.print();
    }
  
    std::cout<<"-------------------------------------------------------"<<std::endl;

    std::pair<Uinmap::iterator,Uinmap::iterator> ret;
    ret = uinmap.equal_range("zhangjun");

    Uinmap::iterator it;    
    for (it=ret.first; it!=ret.second; ++it)
    {
        //it->second.print();
        uinmap.erase(it);
    }

    uit = uinmap.begin();
    for( ; uit != uinmap.end(); ++uit)
    {
        uit->second.print();
    }

    return 0;
}

