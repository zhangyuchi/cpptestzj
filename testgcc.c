#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct foo
{
  char a __attribute__ ((aligned (2))) ;
  int x[2] __attribute__ ((packed));
};

struct bar
{
  char a;
  int x[2]; 
} __attribute__ ((packed));

void __attribute__ ((warning ("af"))) noinvoke() 
{
  printf("noinvoke\n");
}


void __attribute__ ((constructor (101))) begin()
{
  printf("begin\n");
}

void __attribute__ ((constructor (102))) second()
{
  printf("second\n");
}

void __attribute__ ((destructor)) end()
{
  printf("end\n");
}


void * __attribute__((nonnull (1, 2))) my_memcpy (void *dest, const void *src, size_t len) 
{
  return  memcpy(dest, src, len);
}

void __attribute__ ((noreturn)) fatal ()
{
  printf("hello fatal\n"); 
  //_exit(1);
}


int main()
{
  int i __attribute__ ((unused));
  printf("foo size is %lu\n", sizeof(struct foo));
  printf("bar size is %lu\n", sizeof(struct bar));

  noinvoke();
  char *buf = NULL;
  my_memcpy(buf, "af", 12);
  fatal();
  return 0;
}

