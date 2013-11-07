#include <stdio.h>

int g_value=0;

int main()
{
  char buff[]="hello world!";
  printf("%s\n", buff);
  printf("g_value=%d\n", g_value);

  int oldvalue = __atomic_test_and_set(&g_value, __ATOMIC_RELAXED);//set to 1
  printf( "g_value=%d, oldvalue=%d\n", g_value, oldvalue);	

  int ret = __sync_fetch_and_add(&g_value, 1);
  printf( "g_value=%d, ret=%d\n", g_value, ret );

  oldvalue = __atomic_test_and_set(&g_value, __ATOMIC_RELAXED); //set to 1
  printf( "g_value=%d, oldvalue=%d\n", g_value, oldvalue);	

  return 0;
}
