#include <iostream>
#include <boost/noncopyable.hpp>
#include <vector>

using namespace std;

class Object : boost::noncopyable
{
public:
  Object(int id=0)
  :id_(id)
  {} 

private:
  int id_;
};

int main()
{
  Object obj;
  Object& obj1 = obj;
  //Object obj2 = obj; //compile error
  
  vector<Object> objvec;
  //objvec.push_back(obj1); //compile error

  return 0;
}

