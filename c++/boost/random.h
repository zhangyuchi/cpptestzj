#ifndef CONNECT_SERVER_RANDOM_H
#define CONNECT_SERVER_RANDOM_H

#include <stdint.h>
#include <cmath>
#include <boost/random.hpp>

class Random
{
    public:
        Random()
            :gen_(),
             dist_(0x0effffffffffffff, 0xefffffffffffffff),
             die_(gen_,dist_)
        {}

        uint64_t get()
        {
            return static_cast<uint64_t>(die_());
        }

    private:
        boost::mt19937 gen_;                                     
        boost::uniform_real<> dist_;
        boost::variate_generator<boost::mt19937&,boost::uniform_real<> > die_;
};

#endif

