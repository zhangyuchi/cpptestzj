#include <memory>
#include <iostream>

class A: public std::enable_shared_from_this<A>
{
  public:
    std::shared_ptr<A> getptr() {
      return shared_from_this();
    }
};

class B: public std::enable_shared_from_this<B>
{
  public:
    std::shared_ptr<B> getptr() {
      return shared_from_this();
    }
};

class Good: public A, public std::enable_shared_from_this<Good>
{
  public:
    std::shared_ptr<Good> getptr() {
      return std::enable_shared_from_this<Good>::shared_from_this();
    }
};

class Bad
{
  public:
    std::shared_ptr<Bad> getptr() {
      return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

int main()
{
  // Good: the two shared_ptr's share the same object
  std::shared_ptr<Good> gp1(new Good);
  std::shared_ptr<Good> gp2 = gp1->getptr();
  std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';

  // Bad, each shared_ptr thinks it's the only owner of the object
  std::shared_ptr<Bad> bp1(new Bad);
  std::shared_ptr<Bad> bp2 = bp1->getptr();
  std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
}

