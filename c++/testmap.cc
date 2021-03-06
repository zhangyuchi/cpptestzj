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
#include <tr1/unordered_map>
#include <tr1/tuple>
#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

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

class Value
{
public:
  Value():value(255){}

public:  
  int value;
};

class State
{
public:
  State(){}
  int& state(int n)
  {
    return states[n].value;
  } 

  void print(int n)
  {
     for(int i=0; i<10; ++i)
            cout<<states[i].value<<endl; 
  }

private:  
  map<int,Value> states;
};

auto getstate(auto i)
{
  return i;
}

int main()
{
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
  
    std::tr1::unordered_map<int, int> intmap;
    bool is_insert;
    std::tr1::tie(std::tr1::ignore, is_insert) = intmap.insert(std::make_pair(1, 1));
    std::cout<<"insert 1,1 ret="<<is_insert<<" value="<<intmap[1]<<std::endl;
    std::tr1::tie(std::tr1::ignore, is_insert) = intmap.insert(std::make_pair(1, 2));
    std::cout<<"insert 1,2 ret="<<is_insert<<" value="<<intmap[1]<<std::endl;
    std::tr1::tie(std::tr1::ignore, is_insert) = intmap.insert(std::make_pair(1, 3));
    std::cout<<"insert 1,3 ret="<<is_insert<<" value="<<intmap[1]<<std::endl;
  }
  { 
    std::map<int, string> strmap;
    for(int i=0; i<10; ++i)
      cout<<strmap[i].size()<<endl;
  }

  cout<<"----------------------------------"<<endl;

  {
    State s;
    s.print(10);

    for(int i=0; i<10; ++i)
      s.state(i) = i;

    cout<<"================================"<<endl;
    s.print(10);
  }

  {
    cout<<getstate(1.23)<<endl;
  }

  return 0;    
}

