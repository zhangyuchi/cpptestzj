#include <time.h>
#include <cstdio>

int main()
{
  time_t t;

  time(&t);
  //char *ts = ctime(&t);
  tm res;
  tm *ret = localtime_r(&t, &res);
  if (ret)
    printf("time: %d-%02d-%02d %02d:%02d:%02d\n", 1900+res.tm_year, 1+res.tm_mon, res.tm_mday, res.tm_hour, res.tm_min, res.tm_sec);

  return 0;
}

