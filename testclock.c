#define _POSIX_C_SOURCE  199309L
#include <time.h>
#include <stdio.h>

int main()
{
  float f=123.013;

  for(int j=0; j<2; ++j)
  {
    for(int i=0; i<10; ++i)
    {
       
      struct timespec tp;
      //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
      clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
      printf("clock=%d ", tp.tv_nsec);
    }

    printf("\n");  
  }

  return 0;
}
