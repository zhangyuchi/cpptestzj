/*
 * =============================================================================
 *
 *       Filename:  testhashmap.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月23日 18时26分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <sys/time.h>
#include <stdio.h>
#include <vector>
#include <tr1/unordered_map>
#include <febird/hash_strmap.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/shared_ptr.hpp>

typedef std::tr1::unordered_map<std::string, std::string> StrMap;
//typedef hash_strmap<std::string> StrMap;

class Entity
{
    public:
        void insert(const std::string& name, const std::string& id)
        {
            boost::unique_lock<boost::shared_mutex> wLock(mutex_);
            map_.insert( std::make_pair(name, id) );
        }

        void get(const std::string& name, std::vector<std::string> ids)
        {
            boost::shared_lock<boost::shared_mutex> rLock(mutex_);

            StrMap::iterator ret;
            ret = map_.find(name);
            if ( ret!=map_.end() )
                ids.push_back(ret->second);
        }

    private:
        StrMap map_;
        boost::shared_mutex mutex_;
};

Entity ett;

class InsertThread
{
    public:
        InsertThread(int n=0)
            :start_(n)
        {
            stop_flag_ = 0;
        }

        ~InsertThread()
        {}
        
        void set_start(int n)
        {
            start_ = n;
        }

        void stop()
        {
            stop_flag_ = 1;
            thread_obj_->join();
        }

        void run()
        {
            thread_obj_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&InsertThread::svc, this)));
        }

    private:
        int svc()
        {
            for ( int i=start_; i<start_+10000; ++i) 
            {
                char name[32];
                sprintf(name, "test_%d", i);

                struct timeval start_tv;
                struct timeval end_tv;
                gettimeofday(&start_tv, NULL);
                
                std::vector<std::string> ids;
                ett.insert(name, name);

                gettimeofday(&end_tv, NULL);
                double tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
                printf("insert %s spend %ld us\n", name, (long)tt);
            }

            return 0;
        }

    private:
        volatile int stop_flag_;
        int start_;
        boost::shared_ptr<boost::thread> thread_obj_;
};

class GetThread
{
    public:
        GetThread(int n=0)
            :start_(n)
        {
            stop_flag_ = 0;
        }

        void set_start(int n)
        {
            start_ = n;
        }

        ~GetThread()
        {}

        void stop()
        {
            stop_flag_ = 1;
            thread_obj_->join();
        }

        void run()
        {
            thread_obj_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&GetThread::svc, this)));
        }

    private:
        int svc()
        {
            for ( int i=start_; i<start_+10000; ++i) 
            {
                char name[32];
                sprintf(name, "test_%d", i);
                
                struct timeval start_tv;
                struct timeval end_tv;
                gettimeofday(&start_tv, NULL);

                std::vector<std::string> ids;
                ett.get(name, ids);

                gettimeofday(&end_tv, NULL);
                double tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
                printf("get %s spend %ld us\n", name, (long)tt);

            }

            return 0;
        }

    private:
        volatile int stop_flag_;
        int start_;
        boost::shared_ptr<boost::thread> thread_obj_;
};

int main()
{
    InsertThread it[20];
    GetThread gt[20];

    for(int i=0; i<20; ++i)
    {
        it[i].set_start(i*10000);
        it[i].run();                 
    }

    for(int i=0; i<20; ++i)
    {
        it[i].stop();                 
    }

    for(int i=0; i<20; ++i)
    {
        gt[i].set_start(i*10000);
        gt[i].run();         
    }

    for(int i=0; i<20; ++i)
    {
        gt[i].stop();         
    }

    return 0;
}

