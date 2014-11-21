#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class Num
{
public:
  Num(int id):id_(id){cout<<"Num:"<<id_<<endl;}
  ~Num(){cout<<"~Num:"<<id_<<endl;}
private:
  int id_;
};

class Test
{
public: 
  Test(int n):num_(n){cout<<"Test"<<endl;}
  ~Test(){cout<<"~Test:"<<this<<endl;}

  Test(const Test& r)
    :num_(r.num_)
  {
    cout<<"copy Test:"<<this<<endl;
  } 

  Test& operator=(const Test& r)
  {
    num_ = r.num_;
    cout<<"assign Test:"<<this<<endl;
    return *this;
  }

private:
  Num num_;
};

class Entry
{
public:
  Entry(int id):id_(new int(id)){cout<<"Entry"<<endl;}
  ~Entry(){ delete id_; cout<<"~Entry:"<<this<<endl;}

  Entry(Entry&& r)
    :id_(r.id_)
  {
    r.id_ = nullptr;
    cout<<"move entry:"<<this<<endl;
  }

  Entry& operator=(Entry&& r)
  {
    id_ = r.id_;
    r.id_ = nullptr;
    cout<<"assign move entry:"<<this<<endl;
    return *this;
  }

  Entry(const Entry& r) = delete;
  Entry& operator=(const Entry& r) = delete;

private:
  int *id_;
};

int main()
{
  {
    unique_ptr<Test> pT = make_unique<Test>(11);
  }
  //{unique_ptr<Test[]> pTA = unique_ptr<Test[]>(new Test[3]);}
  //{unique_ptr<Test[]> pTA1 = make_unique<Test[]>(3);}
  {
    unique_ptr<vector<Test>> pTA1 = make_unique<vector<Test>>(3,13);
  }

  vector<Entry> vec;
  {
    Entry e(10);
    vec.emplace_back(move(e));
  }  

  return 0;
}
