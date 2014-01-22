#include <math.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    printf("too few args\n");
    return -1;
  }

  int init = atoi(argv[1]);
  int diff = atoi(argv[2]);

  int randnum = rand();
  int ret = init + randnum%diff;
  printf("%d + %d%%%d = %d\n",init, randnum, diff, ret);
  return 0;
}

