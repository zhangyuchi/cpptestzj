#ifndef LAMBDA_B_H
#define LAMBDA_B_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include <deque>
#include <list>
#include <iostream>

using namespace std;
using namespace boost::lambda;
//using namespace boost;

template <typename T>
ostream & operator<<(ostream &os, const list<T>& v )
{
    os<<"[";
    BOOST_FOREACH(T i, v)
    {
        os<<i<<",";
    }

    os<<"]";
    return os;
}

template <typename T>
ostream & operator<<(ostream &os, const list<boost::shared_ptr<T> >& v )
{
    os<<"[";
    BOOST_FOREACH(boost::shared_ptr<T> i, v)
    {
        os<<*i<<",";
    }

    os<<"]";
    return os;
}

template<typename T>
class B : public boost::enable_shared_from_this<B<T> >, private boost::noncopyable
{
public:
    B(std::string id)
    :id_(id)
    {
    }

    ~B()
    {
    }

    void start()
    {
        blist_.push_back(this->shared_from_this());
        cout<<blist_<<endl;
    }

    void stop()
    {
        blist_.remove_if(*_1==id_);
        cout<<blist_<<endl;
    }

    bool operator== (const std::string& id) const
    {   
        return id_ == id;
    }

    std::string id_;
    T phone_;
    static list<boost::shared_ptr<B<T> > > blist_;
};

#endif

