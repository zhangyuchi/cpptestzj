#include <cstdio>
#include <cstdlib>

int main(int argc, char ** argv)
{
  if (argc < 2)
  {
    printf("usage: bits number\n");
    return 0;
  }

  int num = atoi(argv[1]);
  
  int shiftnum = (num-128) >> 31;
  printf("shiftnum = %d\n", shiftnum);
  int sum = ~shiftnum & num;
  printf("sum = %d\n", sum);

  return 0;
}

