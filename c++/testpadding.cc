#include <cstdio>

struct Pad{
  char c1;
  char c2;
  char c3;
  int flag;
};

int main()
{
  Pad pad;
  Pad *ppad=NULL;  

  printf("pad size is %d, ppad size is %d\n", sizeof(pad), sizeof(ppad));

  return 0;
}

