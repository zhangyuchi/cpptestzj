#include <sys/time.h>
#include <cstdio>
#include <map>
#include <tr1/unordered_map>

typedef std::map<int,int> RBMap;
typedef std::tr1::unordered_map<int,int> HTMap;
#define TESTSETLEN 100000

int main()
{
    RBMap rbm;
    HTMap htm;
    double tt;

    struct timeval start_tv;
    struct timeval end_tv;
    
    gettimeofday(&start_tv, NULL);
    for(int i=0; i<TESTSETLEN; ++i)
    {
        rbm[i] = i+1;
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("init rbmap spend %f microseconds\n", tt);

    gettimeofday(&start_tv, NULL);
    for(int i=0; i<TESTSETLEN; ++i)
    {
        htm[i] = i+1;
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("init htmap spend %f microseconds\n", tt);
    printf("---------------------------------------------------------------\n");

    gettimeofday(&start_tv, NULL);
    for(RBMap::iterator i=rbm.begin(); i!=rbm.end(); ++i)
    {
        int step;
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("iter rbmap spend %f microseconds\n", tt);

    gettimeofday(&start_tv, NULL);
    for(HTMap::iterator i=htm.begin(); i!=htm.end(); ++i)
    {
        int step;
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("iter htmap spend %f microseconds\n", tt);
    printf("---------------------------------------------------------------\n");


    int ret=0;

    gettimeofday(&start_tv, NULL);
    for(int i=0; i<TESTSETLEN; ++i)
    {
        ret=rbm[i];
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("serialize read rbmap spend %f microseconds\n", tt);

    gettimeofday(&start_tv, NULL);
    for(int i=0; i<TESTSETLEN; ++i)
    {
        ret=htm[i];
    }
    gettimeofday(&end_tv, NULL);
    tt = end_tv.tv_sec*1000000 + end_tv.tv_usec - start_tv.tv_sec*1000000 - start_tv.tv_usec;
    printf("serialize read htmap spend %f microseconds\n", tt);
    printf("---------------------------------------------------------------\n");
    
    return 0;
}
