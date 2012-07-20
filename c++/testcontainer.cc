/*
 * =============================================================================
 *
 *       Filename:  testcontainer.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月20日 16时10分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

template<typename V>
void print(V& v )
{
    std::cout<<v<<std::endl;
}

template<typename V1,typename V2>
void print(std::pair<V1,V2>& v )
{
    std::cout<<v.first<<"-"<<v.second<<std::endl;
}


template<typename V, template<typename V> class C>
void print(C<V>& cs)
{
    typename C<V>::iterator it = cs.begin();
    for( ;it != cs.end(); ++it )
        print(*it);

   std::cout<<std::endl;     
}

template<typename K, typename V, template<typename K, typename V> class C>
void print(C<K,V>& cs)
{
    typename C<K,V>::iterator it = cs.begin();
    for( ;it != cs.end(); ++it )
        print(*it);

   std::cout<<std::endl;     
}

template<typename V, template<typename V> class C>
void put_to_container(const V& v, C<V>& cs)
{
    typename C<V>::iterator it = cs.begin();
    cs.insert(it,v);
}

template<typename K, typename V, template<typename K, typename V> class C>
void put_to_container(const std::pair<K,V>& v, C<K,V>& cs)
{
    typename C<K,V>::iterator it = cs.begin();
    cs.insert(it,v);
}


int main()
{
    std::vector<int> intv;
    put_to_container(1, intv);
    put_to_container(2, intv);
    print(intv);
    
    std::set<int> ints;
    put_to_container(1, ints);
    put_to_container(2, ints);
    print(ints);

    std::map<int, std::string> intstrm;
    put_to_container(std::make_pair(1,std::string("i am 1")), intstrm);
    put_to_container(std::make_pair(2,std::string("i am 2")), intstrm);
    print(intstrm);

    int d = 6;
    print(d);

    return 0;
}

