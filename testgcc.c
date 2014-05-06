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

void noinvoke() __attribute__ ((warning ("af")));
void noinvoke() 
{
  printf("noinvoke\n");
}

void begin() __attribute__ ((constructor (101)));
void begin()
{
  printf("begin\n");
}

void second() __attribute__ ((constructor (102)));
void second()
{
  printf("second\n");
}

void end() __attribute__ ((destructor));
void end()
{
  printf("end\n");
}

void * my_memcpy (void *dest, const void *src, size_t len) __attribute__((nonnull (1, 2)));
void * my_memcpy (void *dest, const void *src, size_t len) 
{
  return  memcpy(dest, src, len);
}

void fatal () __attribute__ ((noreturn));
void fatal ()
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

