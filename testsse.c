#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <emmintrin.h>

/* SSE2 */
typedef double __v2df __attribute__ ((__vector_size__ (16)));
typedef long long __v2di __attribute__ ((__vector_size__ (16)));
typedef int __v4si __attribute__ ((__vector_size__ (16)));
typedef short __v8hi __attribute__ ((__vector_size__ (16)));
typedef char __v16qi __attribute__ ((__vector_size__ (16)));

void __always_inline 
addtwo1(int16_t* a, int16_t *b, int32_t size){
  int32_t i;

  for (i = 0; i < size; i++) {
    a[i] = b[i] + 2;
  }
}

static void __always_inline 
_addtwo(__v8hi *a, __v8hi *b, const int32_t sz)
{
  __v8hi c = {2,2,2,2,2,2,2,2};

  int32_t i;
  for (i = 0; i < sz; i++) {
    a[i] = b[i] + c;
  }
}

static void __always_inline 
addtwo2(int16_t *a, int16_t *b, const int32_t sz)
{
  _addtwo((__v8hi *) a, (__v8hi *) b, sz/8);
}


void origin()
{
  //const int32_t size = 4194304;
  const int32_t size = 1024;
  int16_t a[size], b[size];

  addtwo1(a, b, size);
}

void fast()
{
  const int32_t size = 1024;
  int16_t a[size], b[size];

  addtwo2(a, b, size);
}

int main(int argc, char** argv)
{
  if (argc<=1)  
  {
    printf("usage: exec origin|fast\n");
  }
  else
  {
    if ( !strcmp(argv[1], "origin") )
      origin();
    else
      fast();
  }
  return 0;
}

