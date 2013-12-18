#include <iostream>

using namespace std;

// Recursive template for general case
template <int N>
struct factorial {
  enum { value = N * factorial<N - 1>::value };
};

// Template specialization for base case
template <>
struct factorial<0> {
  enum { value = 1 };
};

template <int D, typename N>
struct node {
    enum { data = D };
    typedef N next;
};
struct tail {};

template <typename L>
struct sum {
    enum { value = L::data + sum<typename L::next>::value };
};
template <>
struct sum<tail> {
    enum { value = 0 };
};

typedef node<1, node<2, node<3, tail> > > list123;

int main()
{
  enum { result = factorial<5>::value }; // 5 * 4 * 3 * 2 * 1 == 120

  int fr = result;
  cout<<fr<<endl;

  enum { total = sum<list123>::value }; // 1 + 2 + 3 == 6
  fr = total;
  cout<<fr<<endl;

  return 0;
}
